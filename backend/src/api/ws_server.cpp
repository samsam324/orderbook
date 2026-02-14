// Owner: ROLE 5 (UI + Backend WS API)

#include "api/ws_server.hpp"

#include "api/message_bus.hpp"

#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <chrono>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace md::api {
namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
namespace ws = beast::websocket;
using tcp = asio::ip::tcp;

// Minimal WS session that supports server pushed broadcasts
class WsSession : public std::enable_shared_from_this<WsSession> {
public:
  explicit WsSession(tcp::socket socket) : ws_(std::move(socket)) {}

  void start() {
    // Accept websocket handshake (no auth, no subprotocols)
    ws_.set_option(ws::stream_base::timeout::suggested(beast::role_type::server));
    ws_.set_option(ws::stream_base::decorator([](ws::response_type& res) {
      res.set(http::field::server, "md_engine_skeleton");
    }));

    ws_.async_accept([self = shared_from_this()](beast::error_code ec) {
      if (ec) {
        std::cerr << "[ws] accept failed: " << ec.message() << "\n";
        return;
      }
      std::cerr << "[ws] client connected\n";
      self->do_read(); // keep socket alive by reading/discarding
    });
  }

  void send_text(std::string msg) {
    // Queue writes to ensure ordering
    asio::post(ws_.get_executor(), [self = shared_from_this(), m = std::move(msg)]() mutable {
      const bool write_in_progress = !self->out_q_.empty();
      self->out_q_.push_back(std::move(m));
      if (!write_in_progress) self->do_write();
    });
  }

  bool is_open() const { return ws_.is_open(); }

private:
  void do_read() {
    ws_.async_read(in_buf_, [self = shared_from_this()](beast::error_code ec, std::size_t) {
      if (ec) {
        std::cerr << "[ws] client disconnected: " << ec.message() << "\n";
        return;
      }
      self->in_buf_.consume(self->in_buf_.size());
      self->do_read();
    });
  }

  void do_write() {
    ws_.text(true);
    ws_.async_write(asio::buffer(out_q_.front()),
      [self = shared_from_this()](beast::error_code ec, std::size_t) {
        if (ec) {
          std::cerr << "[ws] write failed: " << ec.message() << "\n";
          return;
        }
        self->out_q_.pop_front();
        if (!self->out_q_.empty()) self->do_write();
      });
  }

  ws::stream<tcp::socket> ws_;
  beast::flat_buffer in_buf_;
  std::deque<std::string> out_q_;
};

struct WsServer::Impl {
public:
  Impl(MessageBus& bus, std::uint16_t port)
    : bus_(bus), port_(port), ioc_(1), acceptor_(ioc_), timer_(ioc_) {}

  bool start() {
    beast::error_code ec;

    tcp::endpoint ep{asio::ip::make_address("0.0.0.0", ec), port_};
    if (ec) {
      std::cerr << "[ws] bad bind address: " << ec.message() << "\n";
      return false;
    }

    acceptor_.open(ep.protocol(), ec);
    if (ec) {
      std::cerr << "[ws] open failed: " << ec.message() << "\n";
      return false;
    }

    acceptor_.set_option(asio::socket_base::reuse_address(true), ec);
    acceptor_.bind(ep, ec);
    if (ec) {
      std::cerr << "[ws] bind failed: " << ec.message() << "\n";
      return false;
    }

    acceptor_.listen(asio::socket_base::max_listen_connections, ec);
    if (ec) {
      std::cerr << "[ws] listen failed: " << ec.message() << "\n";
      return false;
    }

    std::cerr << "[ws] listening on ws://localhost:" << port_ << "/ws (skeleton)\n";
    do_accept();
    do_drain_bus();
    return true;
  }

  void run() { ioc_.run(); }

  void stop() {
    beast::error_code ec;
    acceptor_.close(ec);
    timer_.cancel();
    ioc_.stop();
  }

private:
  void do_accept() {
    acceptor_.async_accept([this](beast::error_code ec, tcp::socket socket) {
      if (!ec) {
        auto sess = std::make_shared<WsSession>(std::move(socket));
        {
          std::lock_guard<std::mutex> lk(mu_);
          sessions_.push_back(sess);
        }
        sess->start();
      }
      do_accept();
    });
  }

  void broadcast(std::string msg) {
    std::vector<std::shared_ptr<WsSession>> copy;
    {
      std::lock_guard<std::mutex> lk(mu_);
      // prune closed sessions best effort
      std::vector<std::shared_ptr<WsSession>> alive;
      alive.reserve(sessions_.size());
      for (auto& s : sessions_) {
        if (s && s->is_open()) alive.push_back(s);
      }
      sessions_.swap(alive);
      copy = sessions_;
    }
    for (auto& s : copy) s->send_text(msg);
  }

  void do_drain_bus() {
    // Poll the bus periodically for now. Later: condition_variable or lock free queue
    timer_.expires_after(std::chrono::milliseconds(25));
    timer_.async_wait([this](beast::error_code ec) {
      if (ec) return;

      // Drain a bounded number per tick to keep UI responsive
      for (int i = 0; i < 100; ++i) {
        auto m = bus_.try_consume();
        if (!m) break;
        broadcast(*m);
      }

      do_drain_bus();
    });
  }

  MessageBus& bus_;
  std::uint16_t port_;
  asio::io_context ioc_;
  tcp::acceptor acceptor_;
  asio::steady_timer timer_;

  std::mutex mu_;
  std::vector<std::shared_ptr<WsSession>> sessions_;
};

WsServer::WsServer(MessageBus& bus, std::uint16_t port) : bus_(bus), port_(port) {}

WsServer::~WsServer() { stop(); }

bool WsServer::start() {
  if (running_.exchange(true)) return true;

  impl_ = std::make_unique<Impl>(bus_, port_);
  if (!impl_->start()) {
    impl_.reset();
    running_.store(false);
    return false;
  }

  thread_ = std::thread([this] { impl_->run(); });

  return true;
}

void WsServer::stop() {
  if (!running_.exchange(false)) return;
  if (impl_) impl_->stop();
  if (thread_.joinable()) thread_.join();
  impl_.reset();
}

} // namespace md::api

