// Owner: ROLE 2 (Protocols: MoldUDP64 + ITCH)

#include "protocols/moldudp64.hpp"

#include <iostream>

namespace md::protocols {

MoldUdp64Decoder::MoldUdp64Decoder() = default;

void MoldUdp64Decoder::reset_sequence() {
  expected_next_seq_.reset();
}

bool MoldUdp64Decoder::decode_packet(const std::uint8_t* bytes, std::size_t len, std::vector<MoldMessageView>& out_msgs) {
  // TODO(ROLE2): Implement full MoldUDP64 decode
  // Steps:
  // - Validate len >= 20 bytes header (10+8+2)
  // - Parse session (10 ASCII) and seq (8 ASCII numeric)
  // - Parse message_count (u16 big endian)
  // - For i in [0, message_count):
  //     - parse msg_len (u16 BE) and validate remaining
  //     - create MoldMessageView with mold_seq = base_seq + i
  // - Sequence tracking:
  //     - If expected_next_seq_ exists and base_seq != expected_next_seq_, count gap
  //     - Set expected_next_seq_ = base_seq + message_count
  (void)bytes;
  (void)len;
  out_msgs.clear();

  stats_.packets_decoded++;
  std::cerr << "[moldudp64] decode: not implemented\n";
  return true; // Skeleton: treat as decode-ok but emits no messages
}

} // namespace md::protocols

