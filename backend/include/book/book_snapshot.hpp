// Owner: ROLE 4 (L3 Order Book + Analytics)
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "core/types.hpp"

namespace md::book {

// Aggregated top of book / depth snapshot for UI.
// NOTE: Even though the backend maintains L3 per order state, UI snapshots are typically L2 like.
struct LevelView {
  std::int64_t price_1e4{0};
  std::int64_t qty{0};
  std::uint32_t count{0};
};

struct BookSnapshot {
  core::TimestampNs t_ns{0};
  std::string symbol;
  std::vector<LevelView> bids;
  std::vector<LevelView> asks;
};

} // namespace md::book

