// Owner: ROLE 1 (IO/Networking/PCAP)
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "core/types.hpp"

namespace md::io {

// Requirements (later implementation):
// - Write PCAP global header (DLT_EN10MB)
// - For each packet: write record header + packet bytes
// - Provide helpers to build synthetic Ethernet/IP/UDP framing for MoldUDP64
class PcapWriter final {
public:
  PcapWriter();
  ~PcapWriter();

  PcapWriter(const PcapWriter&) = delete;
  PcapWriter& operator=(const PcapWriter&) = delete;

  bool open(const std::string& path);
  void close();

  // Writes one packet record with provided timestamp + raw link-layer bytes
  bool write_packet(core::TimestampNs t_capture_ns, const std::uint8_t* bytes, std::size_t len);

  std::string last_error() const { return last_error_; }

private:
  void* file_{nullptr}; // FILE*
  std::string last_error_{};
};

} // namespace md::io
