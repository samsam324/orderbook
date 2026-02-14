// Owner: ROLE 1 (IO/Networking/PCAP)

#include "io/pcap_reader.hpp"

#include <iostream>

namespace md::io {

PcapReader::PcapReader() = default;

PcapReader::~PcapReader() {
  close();
}

bool PcapReader::open(const std::string& path) {
  // TODO(ROLE1): Use pcap_open_offline() and store pcap_t* in handle_
  // - Populate last_error_ on failure
  // - Reset stats_
  (void)path;
  last_error_ = "PcapReader::open not implemented";
  std::cerr << "[pcap] open: not implemented\n";
  return false;
}

void PcapReader::close() {
  // TODO(ROLE1): If handle_ != nullptr, call pcap_close(handle_) and null it
  handle_ = nullptr;
}

bool PcapReader::for_each_udp_payload(const std::function<bool(const UdpPayloadView&)>& cb) {
  // TODO(ROLE1): Loop pcap_next_ex(), decode packet bytes into UDP payload, and call cb()
  // For now just emit nothing and treat as successful EOF
  (void)cb;
  std::cerr << "[pcap] replay: not implemented (no packets emitted)\n";
  return true;
}

} // namespace md::io

