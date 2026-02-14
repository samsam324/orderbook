// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <atomic>
#include <cstdint>

namespace md::metrics {

// Central counters (atomic for cheap cross-thread increments)
// Later: group by cache lines to reduce contention
struct Counters {
  std::atomic<std::uint64_t> packets_read{0};
  std::atomic<std::uint64_t> mold_packets_decoded{0};
  std::atomic<std::uint64_t> itch_msgs_decoded{0};
  std::atomic<std::uint64_t> events_applied{0};
  std::atomic<std::uint64_t> sequence_gaps{0};
  std::atomic<std::uint64_t> queue_drops{0};
  std::atomic<std::uint64_t> missing_orders{0};
};

} // namespace md::metrics

