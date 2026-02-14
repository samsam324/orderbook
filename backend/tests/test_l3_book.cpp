// Owner: Integration (tests)
// Fully shared between roles

#include "book/l3_order_book.hpp"

#include <cassert>

int main() {
  md::book::L3OrderBook book(/*symbol_id=*/1);

  md::core::NormalizedEvent ev;
  ev.symbol_id = 1;
  ev.type = md::core::NormalizedEvent::Type::Add;
  ev.order_id = 100;
  ev.side = md::core::Side::Bid;
  ev.price_1e4 = 1'000'000;
  ev.qty = 10;

  assert(book.apply(ev));
  assert(book.check_invariants());
  return 0;
}

