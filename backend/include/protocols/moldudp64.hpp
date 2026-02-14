// Owner: ROLE 2 (Protocols: MoldUDP64 + ITCH)
#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace md::protocols {

// MoldUDP64 header (as on wire ASCII fields).
// Nasdaq MoldUDP64 uses:
// - session: 10 bytes ASCII
// - sequence number: 8 bytes ASCII (numeric, left padded with '0')
// - message count: 2 bytes big endian unsigned integer
//
// Then message_count blocks:
// - [u16 msg_len BE][msg_bytes...]
struct MoldUdp64Header {
  char session[10]{};
  char sequence_ascii[8]{};
  std::uint16_t message_count_be{0};
};

// A single message block extracted from a MoldUDP64 packet
struct MoldMessageView {
  std::uint64_t mold_seq{0};           // computed per message sequence (base + index)
  const std::uint8_t* data{nullptr};   // points into original packet buffer
  std::size_t size{0};                // msg_len
};

struct MoldDecodeStats {
  std::uint64_t packets_decoded{0};
  std::uint64_t messages_decoded{0};
  std::uint64_t sequence_gaps{0};
};

// Skeleton MoldUDP64 decoder

// Requirements (later implementation):
// - Parse header and message blocks from a UDP datagram payload
// - Expose an iterator like API to walk message blocks without allocations
// - Detect sequence gaps between packets; increment counters (no retransmit)
// - Provide helpers for numeric parsing of ASCII sequence field
class MoldUdp64Decoder final {
public:
  MoldUdp64Decoder();

  // Resets expected sequence tracking
  void reset_sequence();

  // Decode one UDP payload buffer into message views
  // Returns false if payload is invalid/truncated
  bool decode_packet(const std::uint8_t* bytes, std::size_t len, std::vector<MoldMessageView>& out_msgs);

  const MoldDecodeStats& stats() const noexcept { return stats_; }
  std::string last_error() const { return last_error_; }

private:
  std::optional<std::uint64_t> expected_next_seq_{};
  MoldDecodeStats stats_{};
  std::string last_error_{};
};

} // namespace md::protocols

