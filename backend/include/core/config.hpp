// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <cstdint>
#include <string>

namespace md::core {

// Skeleton config for CLI flags.
// The app layer (`md::app::Engine::Config`) is the operational config; this type exists to
// keep the repository layout stable and document the CLI surface.
struct Config {
  std::string input{"pcap_replay"};
  std::string queue{"mutex"};
  std::string threads{"single_thread"};
  std::string symbol{"AAPL"};
  std::string pcap{};
  std::string itchbin{};
  std::uint16_t ws_port{8787};
  int speed{1};
  std::uint64_t duration_ms{0}; // 0 means run until externally stopped
};

} // namespace md::core

