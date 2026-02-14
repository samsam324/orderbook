// Owner: Integration (tests)
// Fully shared between roles

#include "protocols/moldudp64.hpp"

#include <cassert>
#include <cstdint>
#include <vector>

int main() {
  md::protocols::MoldUdp64Decoder d;
  std::vector<md::protocols::MoldMessageView> msgs;

  std::uint8_t buf[1] = {0};
  const bool ok = d.decode_packet(buf, sizeof(buf), msgs);
  assert(ok);             // skeleton returns true
  assert(msgs.empty());   // skeleton emits none
  return 0;
}

