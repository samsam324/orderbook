// Owner: ROLE 4 (L3 Order Book + Analytics)
#pragma once

#include <cstdint>
#include <list>
#include <map>
#include <optional>
#include <string>
#include <unordered_map>

#include "core/types.hpp"

namespace md::book {

// L3 order book for a single symbol.
// Maintains per order state and per-price FIFO queues.

// Data structures (per spec):
// - orders_: unordered_map<OrderId, Order>
// - bids_/asks_: map<price_1e4, PriceLevel> (bids sorted ascending by default; for best-bid, use rbegin)
// - each PriceLevel keeps FIFO of order ids (std::list<OrderId>) and aggregate totals

// Removal is O(1) by storing the list iterator inside Order.
class L3OrderBook final {
public:
  struct Order {
    core::OrderId id{0};
    core::Side side{core::Side::Bid};
    std::int64_t price_1e4{0};
    std::int32_t qty{0};
    std::string mpid; // optional, may be empty
    core::TimestampNs ts_last_ns{0};

    // Handle into the FIFO list at the corresponding price level.
    std::list<core::OrderId>::iterator fifo_it{};
  };

  struct PriceLevel {
    std::int64_t price_1e4{0};
    std::int64_t total_qty{0};
    std::uint32_t order_count{0};
    std::list<core::OrderId> fifo;
  };

  struct Stats {
    std::uint64_t adds{0};
    std::uint64_t cancels{0};
    std::uint64_t deletes{0};
    std::uint64_t replaces{0};
    std::uint64_t executes{0};
    std::uint64_t trades{0}; // trades don't affect book but we count them here
    std::uint64_t missing_orders{0}; // cancel/delete/execute on unknown order id
    std::uint64_t invariant_violations{0};
  };

  explicit L3OrderBook(core::SymbolId symbol_id);

  core::SymbolId symbol_id() const noexcept { return symbol_id_; }
  const Stats& stats() const noexcept { return stats_; }

  // Apply a normalized event to the book.
  // Returns false on semantic error (for example a negative qty) and increments violations.
  bool apply(const core::NormalizedEvent& ev);

  // Invariant checks (for tests/debug):
  // - No negative qty
  // - Level totals match sum(order.qty) at that level
  // - Orders referenced by price level exist in orders_
  // - Best bid < best ask when both exist (strict inequality for simple markets)
  bool check_invariants() const;

  // Placeholder getters used by snapshot layer.
  std::optional<std::int64_t> best_bid_price_1e4() const;
  std::optional<std::int64_t> best_ask_price_1e4() const;

private:
  using Levels = std::map<std::int64_t, PriceLevel>;

  bool on_add(const core::NormalizedEvent& ev);
  bool on_cancel(const core::NormalizedEvent& ev);
  bool on_delete(const core::NormalizedEvent& ev);
  bool on_replace(const core::NormalizedEvent& ev);
  bool on_execute(const core::NormalizedEvent& ev);
  bool on_trade(const core::NormalizedEvent& ev);

  Levels& levels_for(core::Side s) { return (s == core::Side::Bid) ? bids_ : asks_; }
  const Levels& levels_for(core::Side s) const { return (s == core::Side::Bid) ? bids_ : asks_; }

  bool remove_order(core::OrderId id);

  core::SymbolId symbol_id_{0};
  Stats stats_{};

  std::unordered_map<core::OrderId, Order> orders_{};
  Levels bids_{};
  Levels asks_{};
};

} // namespace md::book

