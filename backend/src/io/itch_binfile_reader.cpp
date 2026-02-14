// Owner: ROLE 1 (IO/Networking/PCAP)

#include "io/itch_binfile_reader.hpp"

#include <iostream>

namespace md::io {

ItchBinfileReader::ItchBinfileReader() = default;

ItchBinfileReader::~ItchBinfileReader() {
  close();
}

bool ItchBinfileReader::open(const std::string& path) {
  // TODO(ROLE1): fopen(path,"rb"); clear buf_; set last_error_
  (void)path;
  last_error_ = "ItchBinfileReader::open not implemented";
  std::cerr << "[itchbin] open: not implemented\n";
  return false;
}

void ItchBinfileReader::close() {
  // TODO(ROLE1): fclose(file_) if open
  file_ = nullptr;
}

bool ItchBinfileReader::next(MsgView& out) {
  // TODO(ROLE1): read u16 length then read message bytes into buf_
  // For now just no messages
  (void)out;
  return false;
}

} // namespace md::io

