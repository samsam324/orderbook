// Owner: ROLE 5 (UI + Backend WS API)
#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <thread>

namespace md::api {

class MessageBus;

// Intended behavior:
// - Listen on ws://localhost:<port>/ws
// - Accept multiple clients
// - Broadcast messages consumed from MessageBus

// Implementation choice: Boost.Beast (portable, standard)
class WsServer final {
public:
  WsServer(MessageBus& bus, std::uint16_t port);
  ~WsServer();

  WsServer(const WsServer&) = delete;
  WsServer& operator=(const WsServer&) = delete;

  bool start();
  void stop();

private:
  struct Impl;

  MessageBus& bus_;
  std::uint16_t port_{0};
  std::atomic<bool> running_{false};
  std::thread thread_;
  std::unique_ptr<Impl> impl_;
};

} // namespace md::api

