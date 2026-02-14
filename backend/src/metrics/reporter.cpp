// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)

#include "metrics/reporter.hpp"

#include <iostream>

namespace md::metrics {

Reporter::Reporter(Counters& counters, LatencyTracker& decode_lat, LatencyTracker& queue_lat, LatencyTracker& apply_lat)
  : counters_(counters), decode_lat_(decode_lat), queue_lat_(queue_lat), apply_lat_(apply_lat) {}

void Reporter::tick(std::uint64_t t_now_ns) {
  // TODO(ROLE3): configurable period and emit structured stats
  const std::uint64_t period_ns = 1'000'000'000ULL;
  if (last_print_ns_ != 0 && (t_now_ns - last_print_ns_) < period_ns) return;
  last_print_ns_ = t_now_ns;

  const auto d = decode_lat_.snapshot();
  const auto q = queue_lat_.snapshot();
  const auto a = apply_lat_.snapshot();

  std::cerr << "[metrics] packets=" << counters_.packets_read.load()
            << " mold=" << counters_.mold_packets_decoded.load()
            << " itch=" << counters_.itch_msgs_decoded.load()
            << " applied=" << counters_.events_applied.load()
            << " gaps=" << counters_.sequence_gaps.load()
            << " drops=" << counters_.queue_drops.load()
            << " lat_decode_p50(ns)=" << d.p50_ns
            << " lat_queue_p50(ns)=" << q.p50_ns
            << " lat_apply_p50(ns)=" << a.p50_ns
            << "\n";

  if (publish_) {
    // Skeleton payload string; Role 5 will replace with JSON schema
    publish_(std::string("{\"type\":\"stats\",\"note\":\"not implemented\"}"));
  }
}

} // namespace md::metrics

