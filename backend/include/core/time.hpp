// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <cstdint>

namespace md::core {

// Returns a monotonic timestamp in nanoseconds for metrics/latency
// NOTE: This is NOT exchange event time (use ITCH timestamp for that)
std::uint64_t now_steady_ns();

} // namespace md::core

