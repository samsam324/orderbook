// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <cstdint>
#include <string>

namespace md::app {

enum class InputMode {
  PcapReplay,
  ItchBinfileReplay,
  UdpLive,
  SimUdp
};

enum class QueueMode {
  Mutex,
  Ring
};

enum class ThreadMode {
  SingleThread,
  TwoThread
};

struct ModesConfig {
  InputMode input_mode{InputMode::PcapReplay};
  QueueMode queue_mode{QueueMode::Mutex};
  ThreadMode thread_mode{ThreadMode::SingleThread};
};

// Helpers to parse CLI values.
InputMode parse_input_mode(const std::string& s);
QueueMode parse_queue_mode(const std::string& s);
ThreadMode parse_thread_mode(const std::string& s);

} // namespace md::app

