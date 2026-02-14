// Owner: ROLE 1 (IO/Networking/PCAP)
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "core/types.hpp"

namespace md::io {

// Requirements (later implementation):
// - Linux sockets (AF_INET, SOCK_DGRAM)
// - bind to ip:port, recvfrom into preallocated buffer
// - timestamp each datagram with wall-clock ingest time (t_ingest_ns)
class UdpReceiver final {
public:
  struct Datagram {
    std::vector<std::uint8_t> bytes;
    core::TimestampNs t_ingest_ns{0};
  };

  UdpReceiver();
  ~UdpReceiver();

  UdpReceiver(const UdpReceiver&) = delete;
  UdpReceiver& operator=(const UdpReceiver&) = delete;

  bool bind(const std::string& ip, std::uint16_t port);
  void close();

  // Blocking receive. Returns false if not implemented / error.
  bool recv(Datagram& out);

  std::string last_error() const { return last_error_; }

private:
  int fd_{-1};
  std::string last_error_{};
};

} // namespace md::io

