// Owner: ROLE 1 (IO/Networking/PCAP)
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "core/types.hpp"

namespace md::io {

// Reader for Nasdaq historical ITCH binfiles (length prefixed ITCH messages)

// The reality: historical files are not PCAP and not MoldUDP64
// We support this via input mode `itch_binfile_replay`

// Expected format (to be confirmed per dataset):
// - Repeating: [u16 length][length bytes of ITCH message]
// - Some distributions may use u16 big endian length
class ItchBinfileReader final {
public:
  struct MsgView {
    const std::uint8_t* data{nullptr};
    std::size_t size{0};
    // ITCH timestamp is inside each message
  };

  ItchBinfileReader();
  ~ItchBinfileReader();

  ItchBinfileReader(const ItchBinfileReader&) = delete;
  ItchBinfileReader& operator=(const ItchBinfileReader&) = delete;

  bool open(const std::string& path);
  void close();

  // Reads next length prefixed message into internal buffer and returns view
  // Returns false on EOF or error (distinguish via last_error_ later)
  bool next(MsgView& out);

  std::string last_error() const { return last_error_; }

private:
  void* file_{nullptr}; // FILE*
  std::vector<std::uint8_t> buf_{};
  std::string last_error_{};
};

} // namespace md::io

