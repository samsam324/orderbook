// Owner: ROLE 4 (L3 Order Book + Analytics)
#pragma once

#include <cstdint>

namespace md::book {

// Placeholder analytics computed from the book and event stream.
// Later:
// - active_orders
// - spread, mid
// - cancels/sec, executes/sec, trades/sec
// - queue position / FIFO estimates
struct AnalyticsSnapshot {
  std::uint64_t active_orders{0};
  std::int64_t spread_1e4{0};
};

} // namespace md::book

