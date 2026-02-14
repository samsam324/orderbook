// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include "metrics/counters.hpp"
#include "metrics/latency.hpp"

namespace md::metrics {

// Periodic reporter that prints to stdout and optionally publishes JSON like strings to UI
class Reporter final {
public:
  using PublishFn = std::function<void(std::string)>;

  Reporter(Counters& counters, LatencyTracker& decode_lat, LatencyTracker& queue_lat, LatencyTracker& apply_lat);

  void set_publish_fn(PublishFn fn) { publish_ = std::move(fn); }

  // Call periodically from engine main loop or a dedicated thread
  void tick(std::uint64_t t_now_ns);

private:
  Counters& counters_;
  LatencyTracker& decode_lat_;
  LatencyTracker& queue_lat_;
  LatencyTracker& apply_lat_;
  PublishFn publish_{};
  std::uint64_t last_print_ns_{0};
};

} // namespace md::metrics

