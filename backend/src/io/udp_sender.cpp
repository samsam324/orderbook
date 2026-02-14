// Owner: ROLE 1 (IO/Networking/PCAP)

#include "io/udp_sender.hpp"

#include <iostream>

namespace md::io {

UdpSender::UdpSender() = default;

UdpSender::~UdpSender() {
  close();
}

bool UdpSender::open() {
  // TODO(ROLE1): Create UDP socket for sending
  last_error_ = "UdpSender::open not implemented";
  std::cerr << "[udp] sender open: not implemented\n";
  return false;
}

void UdpSender::close() {
  // TODO(ROLE1): close(fd_)
  fd_ = -1;
}

bool UdpSender::send_to(const std::string& ip, std::uint16_t port, const std::uint8_t* bytes, std::size_t len) {
  // TODO(ROLE1): sendto() datagram
  (void)ip;
  (void)port;
  (void)bytes;
  (void)len;
  std::cerr << "[udp] send_to: not implemented\n";
  return false;
}

} // namespace md::io

