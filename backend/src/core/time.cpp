// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)

#include "core/time.hpp"

#include <chrono>

namespace md::core {

std::uint64_t now_steady_ns() {
  const auto now = std::chrono::steady_clock::now().time_since_epoch();
  return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
}

} // namespace md::core

