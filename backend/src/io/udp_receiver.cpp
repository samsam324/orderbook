// Owner: ROLE 1 (IO/Networking/PCAP)

#include "io/udp_receiver.hpp"

#include <iostream>

namespace md::io {

UdpReceiver::UdpReceiver() = default;

UdpReceiver::~UdpReceiver() {
  close();
}

bool UdpReceiver::bind(const std::string& ip, std::uint16_t port) {
  // TODO(ROLE1): Create socket, set SO_REUSEADDR, bind
  (void)ip;
  (void)port;
  last_error_ = "UdpReceiver::bind not implemented";
  std::cerr << "[udp] bind: not implemented\n";
  return false;
}

void UdpReceiver::close() {
  // TODO(ROLE1): close(fd_) on Linux
  fd_ = -1;
}

bool UdpReceiver::recv(Datagram& out) {
  // TODO(ROLE1): recvfrom into buffer; set out.t_ingest_ns; swap bytes
  (void)out;
  std::cerr << "[udp] recv: not implemented\n";
  return false;
}

} // namespace md::io

