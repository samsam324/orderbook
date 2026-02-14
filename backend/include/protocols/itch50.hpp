// Owner: ROLE 2 (Protocols: MoldUDP64 + ITCH)
#pragma once

#include <cstdint>

namespace md::protocols::itch50 {

// Skeleton ITCH 5.0 message type tags (1 byte)
// Implemented subset for L3 reconstruction:
// - System Event: 'S'
// - Stock Directory: 'R'
// - Add Order: 'A'
// - Add Order w/ MPID: 'F'
// - Order Executed: 'E'
// - Order Executed with Price: 'C'
// - Order Cancel: 'X'
// - Order Delete: 'D'
// - Order Replace: 'U'
// - Trade (non-cross): 'P'

// IMPORTANT: ITCH is fixed field, big endian numeric, and space padded ASCII for symbols
// This file intentionally does NOT define packed structs yet
// The decoder will parse using explicit offsets per Nasdaq spec

constexpr std::uint8_t MSG_SYSTEM_EVENT = 'S';
constexpr std::uint8_t MSG_STOCK_DIRECTORY = 'R';
constexpr std::uint8_t MSG_ADD_ORDER = 'A';
constexpr std::uint8_t MSG_ADD_ORDER_MPID = 'F';
constexpr std::uint8_t MSG_ORDER_EXECUTED = 'E';
constexpr std::uint8_t MSG_ORDER_EXECUTED_WITH_PRICE = 'C';
constexpr std::uint8_t MSG_ORDER_CANCEL = 'X';
constexpr std::uint8_t MSG_ORDER_DELETE = 'D';
constexpr std::uint8_t MSG_ORDER_REPLACE = 'U';
constexpr std::uint8_t MSG_TRADE = 'P';

// TODO(ROLE2): Add per message length constants and offset tables
// Example: System Event is 12 bytes (type + stock_locate + tracking + ts + event_code)

} // namespace md::protocols::itch50

