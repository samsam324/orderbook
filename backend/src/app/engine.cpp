// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)

#include "app/engine.hpp"

#include <chrono>
#include <iostream>
#include <thread>

// Forward declared API types. definitions provided by Role 5
#include "api/message_bus.hpp"
#include "api/ws_server.hpp"
#include "metrics/latency.hpp"
#include "metrics/reporter.hpp"

namespace md::app {

Engine::Engine(Config cfg) : cfg_(std::move(cfg)) {}

Engine::~Engine() {
  stop();
}

bool Engine::start() {
  if (running_.exchange(true)) return true;

  std::cerr << "[engine] starting (skeleton)\n";
  std::cerr << "  symbol=" << cfg_.symbol << "\n";
  std::cerr << "  ws_port=" << cfg_.ws_port << "\n";
  std::cerr << "  speed=" << cfg_.speed << "\n";
  std::cerr << "  queue_capacity=" << cfg_.queue_capacity << "\n";

  bus_ = std::make_unique<md::api::MessageBus>(4096);
  ws_ = std::make_unique<md::api::WsServer>(*bus_, cfg_.ws_port);

  if (!ws_->start()) {
    std::cerr << "[engine] ws server failed to start (still skeleton)\n";
  }

  return true;
}

void Engine::stop() {
  if (!running_.exchange(false)) return;
  if (ws_) ws_->stop();
}

void Engine::run() {
  metrics::LatencyTracker decode_lat, queue_lat, apply_lat;
  metrics::Reporter reporter(counters_, decode_lat, queue_lat, apply_lat);
  reporter.set_publish_fn([this](std::string s) {
    if (bus_) bus_->try_publish(std::move(s));
  });

  while (running_.load()) {
    // For now just increment some counters and emit placeholder stats
    counters_.packets_read.fetch_add(1);
    const auto now = std::chrono::steady_clock::now().time_since_epoch();
    const std::uint64_t t_now_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
    reporter.tick(t_now_ns);

    // For now publish a placeholder snapshot occasionally
    if (bus_) bus_->try_publish(std::string("{\"type\":\"snapshot\",\"note\":\"not implemented\"}"));

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

} // namespace md::app

