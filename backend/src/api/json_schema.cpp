// Owner: ROLE 5 (UI + Backend WS API)

#include "api/json_schema.hpp"

namespace md::api {

std::string make_event_json(std::uint64_t seq, const core::EventFrame& frame, const std::string& symbol) {
  // TODO(ROLE5): Use nlohmann::json and include normalized fields
  (void)seq;
  (void)frame;
  (void)symbol;
  return std::string("{\"type\":\"event\",\"note\":\"not implemented\"}");
}

std::string make_snapshot_json(const book::BookSnapshot& snap) {
  // TODO(ROLE5): Serialize levels + counts
  (void)snap;
  return std::string("{\"type\":\"snapshot\",\"note\":\"not implemented\"}");
}

std::string make_stats_json(std::uint64_t t_ns, const std::string& symbol) {
  // TODO(ROLE5): Serialize rates + latency percentiles + book stats
  (void)t_ns;
  (void)symbol;
  return std::string("{\"type\":\"stats\",\"note\":\"not implemented\"}");
}

} // namespace md::api

