// Owner: ROLE 5 (UI + Backend WS API)
#pragma once

#include <cstdint>
#include <string>

#include "book/book_snapshot.hpp"
#include "core/types.hpp"

namespace md::api {

// Requirements:
// - Use nlohmann::json to build structured payloads:
//   1) event
//   2) snapshot
//   3) stats
// - Keep payloads bounded (truncate tape, truncate L3 depth lists)
// - Ensure field names match UI expectations

std::string make_event_json(std::uint64_t seq, const core::EventFrame& frame, const std::string& symbol);
std::string make_snapshot_json(const book::BookSnapshot& snap);
std::string make_stats_json(std::uint64_t t_ns, const std::string& symbol);

} // namespace md::api

