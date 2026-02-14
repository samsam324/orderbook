// Owner: ROLE 2 (Protocols) with consumers across all roles
#pragma once

#include <cstdint>
#include <cstddef>

namespace md::core {

// Fundamental ids/timestamps
using TimestampNs = std::uint64_t;
using SymbolId = std::uint32_t;
using OrderId = std::uint64_t;

enum class Side : std::uint8_t { Bid = 0, Ask = 1 };

// Raw ITCH message view
struct ItchMsg {
  const std::uint8_t* data{nullptr};
  std::size_t size{0};
};

// Normalized event emitted by protocol decoding stage.
// This is the only format the book needs to understand
struct NormalizedEvent {
  enum class Type : std::uint8_t {
    Add,
    Cancel,
    Delete,
    Replace,
    Execute,
    Trade,
    System,
    StockDirectory
  };

  Type type{Type::System};

  SymbolId symbol_id{0};
  OrderId order_id{0};
  Side side{Side::Bid};

  // Prices are in 1e-4 dollars (ITCH implied 4 decimals)
  // Example: $101.2345 -> price_1e4 = 1'012'345
  std::int64_t price_1e4{0};
  std::int32_t qty{0};

  // Replace fields (cancel/replace semantics)
  OrderId new_order_id{0};
  std::int64_t new_price_1e4{0};
  std::int32_t new_qty{0};

  // Match/trade fields (if available by message type)
  std::uint64_t match_id{0};
  bool printable{false};

  // Event time: ITCH timestamp nanoseconds since midnight
  TimestampNs ts_event_ns{0};
};

// EventFrame wraps a NormalizedEvent and adds pipeline timestamps for latency tracking
struct EventFrame {
  NormalizedEvent ev{};

  TimestampNs t_ingest_ns{0};
  TimestampNs t_decode_ns{0};
  TimestampNs t_enqueue_ns{0};
  TimestampNs t_dequeue_ns{0};
  TimestampNs t_apply_ns{0};
};

} // namespace md::core

