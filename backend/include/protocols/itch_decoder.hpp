// Owner: ROLE 2 (Protocols: MoldUDP64 + ITCH)
#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include "core/types.hpp"

namespace md::protocols {

// Maintains mapping from ITCH Stock Locate to symbol string and a compact SymbolId

// Stock Directory ('R') provides:
// - stock_locate (u16) and stock symbol (8 bytes ASCII, space padded)

// Decoder uses this registry to:
// - filter events to a configured target symbol (e.g. "AAPL")
// - convert stock_locate -> SymbolId
class SymbolRegistry final {
public:
  struct Entry {
    core::SymbolId symbol_id{0};
    std::string symbol; // canonical trimmed
  };

  // Adds/updates mapping; returns the SymbolId
  core::SymbolId upsert(std::uint16_t stock_locate, std::string symbol);

  std::optional<Entry> lookup(std::uint16_t stock_locate) const;

  // Set desired filter; empty -> accept all symbols
  void set_filter_symbol(std::string symbol);
  const std::string& filter_symbol() const noexcept { return filter_symbol_; }

  // Returns true if stock_locate maps to filter symbol (or filter disabled)
  bool passes_filter(std::uint16_t stock_locate) const;

private:
  std::unordered_map<std::uint16_t, Entry> map_{};
  core::SymbolId next_symbol_id_{1};
  std::string filter_symbol_{};
};

struct ItchDecodeStats {
  std::uint64_t msgs_total{0};
  std::uint64_t msgs_supported{0};
  std::uint64_t msgs_filtered_out{0};
  std::uint64_t decode_errors{0};
};

// Skeleton ITCH 5.0 decoder (subset)

// Requirements (later implementation):
// - Parse fixed format ITCH messages by type
// - Extract ITCH timestamp: nanoseconds since midnight (u48)
// - Produce core::NormalizedEvent for supported message types
// - Maintain per order state is in book layer while decoder only normalizes
// - Handle cancel/delete/execute before add (partial datasets) by incrementing counters upstream
class ItchDecoder final {
public:
  ItchDecoder();

  void set_filter_symbol(std::string symbol);
  SymbolRegistry& registry() noexcept { return registry_; }
  const ItchDecodeStats& stats() const noexcept { return stats_; }
  std::string last_error() const { return last_error_; }

  // Decode one ITCH message (without Mold framing)
  // Returns nullopt if message is unsupported/filtered and returns event on success
  std::optional<core::NormalizedEvent> decode_one(const std::uint8_t* bytes, std::size_t len);

private:
  SymbolRegistry registry_{};
  ItchDecodeStats stats_{};
  std::string last_error_{};
};

} // namespace md::protocols

