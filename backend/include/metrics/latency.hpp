// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <cstdint>

namespace md::metrics {

// Requirements (later implementation):
// - Record sampled latency values (ns) for decode/queue/apply/e2e
// - Compute percentiles p50/p95/p99 periodically (we will later use these stats to beef up our resumes)
// - Use a streaming sketch (t-digest, HDR histogram, CKMS, etc.)
class LatencyTracker final {
public:
  void record_ns(std::uint64_t v_ns) {
    // TODO(ROLE3): implement sketch insert
    (void)v_ns;
    samples_++;
  }

  struct Snapshot {
    std::uint64_t samples{0};
    std::uint64_t p50_ns{0};
    std::uint64_t p95_ns{0};
    std::uint64_t p99_ns{0};
  };

  Snapshot snapshot() const {
    // TODO(ROLE3): compute percentiles from sketch
    return Snapshot{samples_, 0, 0, 0};
  }

private:
  std::uint64_t samples_{0};
};

} // namespace md::metrics

