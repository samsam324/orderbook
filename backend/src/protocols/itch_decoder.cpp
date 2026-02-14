// Owner: ROLE 2 (Protocols: MoldUDP64 + ITCH)

#include "protocols/itch_decoder.hpp"

#include "protocols/itch50.hpp"

#include <iostream>

namespace md::protocols {

core::SymbolId SymbolRegistry::upsert(std::uint16_t stock_locate, std::string symbol) {
  auto it = map_.find(stock_locate);
  if (it == map_.end()) {
    Entry e;
    e.symbol_id = next_symbol_id_++;
    e.symbol = std::move(symbol);
    map_.emplace(stock_locate, std::move(e));
    return map_.at(stock_locate).symbol_id;
  }
  it->second.symbol = std::move(symbol);
  return it->second.symbol_id;
}

std::optional<SymbolRegistry::Entry> SymbolRegistry::lookup(std::uint16_t stock_locate) const {
  auto it = map_.find(stock_locate);
  if (it == map_.end()) return std::nullopt;
  return it->second;
}

void SymbolRegistry::set_filter_symbol(std::string symbol) {
  filter_symbol_ = std::move(symbol);
}

bool SymbolRegistry::passes_filter(std::uint16_t stock_locate) const {
  if (filter_symbol_.empty()) return true;
  auto it = map_.find(stock_locate);
  if (it == map_.end()) return false;
  return it->second.symbol == filter_symbol_;
}

ItchDecoder::ItchDecoder() = default;

void ItchDecoder::set_filter_symbol(std::string symbol) {
  registry_.set_filter_symbol(std::move(symbol));
}

std::optional<core::NormalizedEvent> ItchDecoder::decode_one(const std::uint8_t* bytes, std::size_t len) {
  stats_.msgs_total++;
  if (len < 1 || bytes == nullptr) {
    stats_.decode_errors++;
    last_error_ = "decode_one: empty buffer";
    return std::nullopt;
  }

  const std::uint8_t type = bytes[0];

  // TODO(ROLE2): Implement per message fixed offset parsing using Nasdaq ITCH 5.0 spec
  // This skeleton currently returns no events but keeps the dispatch structure
  switch (type) {
    case itch50::MSG_SYSTEM_EVENT:
    case itch50::MSG_STOCK_DIRECTORY:
    case itch50::MSG_ADD_ORDER:
    case itch50::MSG_ADD_ORDER_MPID:
    case itch50::MSG_ORDER_EXECUTED:
    case itch50::MSG_ORDER_EXECUTED_WITH_PRICE:
    case itch50::MSG_ORDER_CANCEL:
    case itch50::MSG_ORDER_DELETE:
    case itch50::MSG_ORDER_REPLACE:
    case itch50::MSG_TRADE:
      stats_.msgs_supported++;
      std::cerr << "[itch] decode_one: not implemented for type '" << char(type) << "'\n";
      return std::nullopt;
    default:
      // Unsupported message type
      return std::nullopt;
  }
}

} // namespace md::protocols

