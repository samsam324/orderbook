// Owner: Integration (tests)
// Fully shared between roles

#include "protocols/itch_decoder.hpp"

#include <cassert>
#include <cstdint>

int main() {
  md::protocols::ItchDecoder dec;
  dec.set_filter_symbol("AAPL");

  // Feed a few message type bytes to ensure dispatch paths compile
  const std::uint8_t addA[1] = {'A'};
  const std::uint8_t sysS[1] = {'S'};
  const std::uint8_t tradeP[1] = {'P'};

  (void)dec.decode_one(addA, sizeof(addA));
  (void)dec.decode_one(sysS, sizeof(sysS));
  (void)dec.decode_one(tradeP, sizeof(tradeP));

  assert(dec.stats().msgs_total == 3);
  return 0;
}

