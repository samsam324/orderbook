// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)

#include "app/modes.hpp"

namespace md::app {

InputMode parse_input_mode(const std::string& s) {
  if (s == "pcap_replay") return InputMode::PcapReplay;
  if (s == "itch_binfile_replay") return InputMode::ItchBinfileReplay;
  if (s == "udp_live") return InputMode::UdpLive;
  if (s == "sim_udp") return InputMode::SimUdp;
  return InputMode::PcapReplay;
}

QueueMode parse_queue_mode(const std::string& s) {
  if (s == "ring") return QueueMode::Ring;
  return QueueMode::Mutex;
}

ThreadMode parse_thread_mode(const std::string& s) {
  if (s == "two_thread") return ThreadMode::TwoThread;
  return ThreadMode::SingleThread;
}

} // namespace md::app

