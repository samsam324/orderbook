// Owner: ROLE 1 (IO/Networking/PCAP)

#include "io/pcap_writer.hpp"

#include <cstdio>
#include <iostream>

namespace md::io {

PcapWriter::PcapWriter() = default;

PcapWriter::~PcapWriter() {
  close();
}

bool PcapWriter::open(const std::string& path) {
  // TODO(ROLE1): Open file in binary mode and write PCAP global header
  (void)path;
  last_error_ = "PcapWriter::open not implemented";
  std::cerr << "[pcap] writer open: not implemented\n";
  return false;
}

void PcapWriter::close() {
  // TODO(ROLE1): fclose(file_) if open
  file_ = nullptr;
}

bool PcapWriter::write_packet(core::TimestampNs t_capture_ns, const std::uint8_t* bytes, std::size_t len) {
  // TODO(ROLE1): Write PCAP record header using t_capture_ns and payload length, then bytes
  (void)t_capture_ns;
  (void)bytes;
  (void)len;
  std::cerr << "[pcap] writer packet: not implemented\n";
  return false;
}

} // namespace md::io

