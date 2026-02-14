// Owner: ROLE 1 (IO/Networking/PCAP)
#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

#include "core/types.hpp"

namespace md::io {

// A lightweight view of a captured UDP payload extracted from a PCAP packet
// The backend pipeline treats this as a MoldUDP64 datagram payload
struct UdpPayloadView {
  const std::uint8_t* data{nullptr};
  std::size_t size{0};
  core::TimestampNs t_capture_ns{0};  // wall-clock capture time (PCAP record)
};

// Requirements (later implementation):
// - Open standard libpcap .pcap files.
// - Iterate packets and decode Ethernet -> IPv4 -> UDP headers.
// - Extract UDP payload bytes (datagram payload) and pass to callback.
// - Preserve packet timestamps from PCAP record header.

// Edge cases:
// - VLAN tags
// - IPv6
// - Non UDP packets
// - Truncated capture length
class PcapReader final {
public:
  struct Stats {
    std::uint64_t packets_total{0};
    std::uint64_t packets_udp{0};
    std::uint64_t packets_skipped{0};
    std::uint64_t payloads_emitted{0};
  };

  PcapReader();
  ~PcapReader();

  PcapReader(const PcapReader&) = delete;
  PcapReader& operator=(const PcapReader&) = delete;

  bool open(const std::string& path);
  void close();

  // Iterate packets until End of File (this is also called EOF) or until callback returns false
  // Returns false on read error and true on normal termination
  bool for_each_udp_payload(const std::function<bool(const UdpPayloadView&)>& cb);

  const Stats& stats() const noexcept { return stats_; }
  std::string last_error() const { return last_error_; }

private:
  void* handle_{nullptr}; // pcap_t* (opaque in header to avoid including pcap.h)
  Stats stats_{};
  std::string last_error_{};
};

} // namespace md::io

