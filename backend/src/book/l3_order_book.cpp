// Owner: ROLE 4 (L3 Order Book + Analytics)

#include "book/l3_order_book.hpp"

#include <iostream>

namespace md::book {

L3OrderBook::L3OrderBook(core::SymbolId symbol_id) : symbol_id_(symbol_id) {}

bool L3OrderBook::apply(const core::NormalizedEvent& ev) {
  if (ev.symbol_id != symbol_id_) {
    // Single symbol book so we ignore other symbols.
    return true;
  }

  bool ok = true;
  switch (ev.type) {
    case core::NormalizedEvent::Type::Add: ok = on_add(ev); break;
    case core::NormalizedEvent::Type::Cancel: ok = on_cancel(ev); break;
    case core::NormalizedEvent::Type::Delete: ok = on_delete(ev); break;
    case core::NormalizedEvent::Type::Replace: ok = on_replace(ev); break;
    case core::NormalizedEvent::Type::Execute: ok = on_execute(ev); break;
    case core::NormalizedEvent::Type::Trade: ok = on_trade(ev); break;
    case core::NormalizedEvent::Type::System:
    case core::NormalizedEvent::Type::StockDirectory:
      // No book impact
      ok = true;
      break;
  }

  if (!ok) {
    stats_.invariant_violations++;
  }
  return ok;
}

bool L3OrderBook::check_invariants() const {
  // TODO(ROLE4): Implement full invariant checks described in header
  return true;
}

std::optional<std::int64_t> L3OrderBook::best_bid_price_1e4() const {
  if (bids_.empty()) return std::nullopt;
  return bids_.rbegin()->first;
}

std::optional<std::int64_t> L3OrderBook::best_ask_price_1e4() const {
  if (asks_.empty()) return std::nullopt;
  return asks_.begin()->first;
}

bool L3OrderBook::on_add(const core::NormalizedEvent& ev) {
  stats_.adds++;
  // TODO(ROLE4):
  // - Validate qty > 0, price_1e4 > 0
  // - Insert into orders_ with fifo iterator
  // - Update PriceLevel totals and counts
  // - Handle duplicate order id (count violation and decide overwrite or reject)
  (void)ev;
  std::cerr << "[book] add: not implemented\n";
  return true;
}

bool L3OrderBook::on_cancel(const core::NormalizedEvent& ev) {
  stats_.cancels++;
  // TODO(ROLE4):
  // - Find order and if missing, stats_.missing_orders++ and return true
  // - Reduce qty by ev.qty (canceled shares)
  // - If qty reaches 0, remove order (from FIFO + map)
  // - Prevent negative qty
  (void)ev;
  std::cerr << "[book] cancel: not implemented\n";
  return true;
}

bool L3OrderBook::on_delete(const core::NormalizedEvent& ev) {
  stats_.deletes++;
  // TODO(ROLE4):
  // - Remove order fully; if missing, stats_.missing_orders++
  (void)ev;
  std::cerr << "[book] delete: not implemented\n";
  return true;
}

bool L3OrderBook::on_replace(const core::NormalizedEvent& ev) {
  stats_.replaces++;
  // TODO(ROLE4):
  // Replace semantics (Nasdaq 'U'):
  // - Remove old order id (remaining shares removed)
  // - Add new_order_id at new_price/new_qty
  // - Side and symbol unchanged by spec (decoder enforces)
  (void)ev;
  std::cerr << "[book] replace: not implemented\n";
  return true;
}

bool L3OrderBook::on_execute(const core::NormalizedEvent& ev) {
  stats_.executes++;
  // TODO(ROLE4):
  // - Reduce qty by executed shares (ev.qty)
  // - If qty==0 remove
  // - If printable update trade stats (analytics)
  (void)ev;
  std::cerr << "[book] execute: not implemented\n";
  return true;
}

bool L3OrderBook::on_trade(const core::NormalizedEvent& ev) {
  stats_.trades++;
  // TODO(ROLE4):
  // - Trades do not alter book; update tape/stats only
  (void)ev;
  return true;
}

bool L3OrderBook::remove_order(core::OrderId id) {
  // TODO(ROLE4): O(1) remove using stored iterator
  (void)id;
  return false;
}

} // namespace md::book

