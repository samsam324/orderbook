// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <string>

#include "app/modes.hpp"
#include "core/types.hpp"
#include "metrics/counters.hpp"

namespace md::api {
class MessageBus;
class WsServer;
} // namespace md::api

namespace md::app {

// Main orchestration engine.

// Pipeline:
// - ingest: pcap / itchbin / udp / sim_udp
// - decode: MoldUDP64 -> ITCH -> NormalizedEvent
// - enqueue: mutex queue or spsc ring
// - apply: L3 order book
// - publish: WS event/snapshot/stats

class Engine final {
public:
  struct Config {
    ModesConfig modes{};
    std::string symbol{"AAPL"};
    std::string pcap_path{};
    std::string itchbin_path{};
    std::uint16_t ws_port{8787};
    int speed{1};
    std::size_t queue_capacity{1 << 16};
  };

  explicit Engine(Config cfg);
  ~Engine();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

  bool start();
  void stop();

  // Blocks until stopped (skeleton: sleeps/polls).
  void run();

  metrics::Counters& counters() noexcept { return counters_; }

private:
  Config cfg_;
  std::atomic<bool> running_{false};
  metrics::Counters counters_{};

  // Role 5 will implement these.
  std::unique_ptr<api::MessageBus> bus_;
  std::unique_ptr<api::WsServer> ws_;
};

} // namespace md::app

