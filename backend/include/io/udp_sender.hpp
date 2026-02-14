// Owner: ROLE 1 (IO/Networking/PCAP)
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace md::io {

// Skeleton UDP sender for simulated MoldUDP64 feed.
//
// Requirements (later implementation):
// - Linux sockets sendto
// - configurable destination ip:port
class UdpSender final {
public:
  UdpSender();
  ~UdpSender();

  UdpSender(const UdpSender&) = delete;
  UdpSender& operator=(const UdpSender&) = delete;

  bool open();
  void close();

  bool send_to(const std::string& ip, std::uint16_t port, const std::uint8_t* bytes, std::size_t len);

  std::string last_error() const { return last_error_; }

private:
  int fd_{-1};
  std::string last_error_{};
};

} // namespace md::io

