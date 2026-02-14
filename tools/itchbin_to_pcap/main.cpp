// Owner: ROLE 1 (IO/Networking/PCAP) + ROLE 2 (Protocols)

#include <cstdlib>
#include <iostream>
#include <string>

namespace {

struct Args {
  std::string in_path{};
  std::string out_path{};
  std::string symbol{};
  int msgs_per_pkt{30};
};

void print_usage() {
  std::cerr
    << "itchbin_to_pcap (skeleton)\n"
    << "Usage:\n"
    << "  itchbin_to_pcap --in <ITCH_BIN> --out <OUT_PCAP> [--symbol AAPL] [--msgs_per_pkt 30]\n";
}

bool parse_args(int argc, char** argv, Args& out) {
  for (int i = 1; i < argc; ++i) {
    const std::string a = argv[i];
    auto need_val = [&](const char* flag) -> const char* {
      if (i + 1 >= argc) {
        std::cerr << "Missing value for " << flag << "\n";
        return nullptr;
      }
      return argv[++i];
    };

    if (a == "--in") {
      const char* v = need_val("--in");
      if (!v) return false;
      out.in_path = v;
    } else if (a == "--out") {
      const char* v = need_val("--out");
      if (!v) return false;
      out.out_path = v;
    } else if (a == "--symbol") {
      const char* v = need_val("--symbol");
      if (!v) return false;
      out.symbol = v;
    } else if (a == "--msgs_per_pkt") {
      const char* v = need_val("--msgs_per_pkt");
      if (!v) return false;
      out.msgs_per_pkt = std::atoi(v);
    } else if (a == "--help" || a == "-h") {
      print_usage();
      return false;
    } else {
      std::cerr << "Unknown arg: " << a << "\n";
      return false;
    }
  }
  return !out.in_path.empty() && !out.out_path.empty();
}

} // namespace

int main(int argc, char** argv) {
  Args args;
  if (!parse_args(argc, argv, args)) {
    print_usage();
    return 2;
  }

  std::cerr << "[itchbin_to_pcap] not implemented\n";
  std::cerr << "  in: " << args.in_path << "\n";
  std::cerr << "  out: " << args.out_path << "\n";
  std::cerr << "  symbol: " << (args.symbol.empty() ? "(none)" : args.symbol) << "\n";
  std::cerr << "  msgs_per_pkt: " << args.msgs_per_pkt << "\n";

  // TODO(ROLE1+ROLE2):
  // - Read length prefixed ITCH messages from args.in_path
  // - Group messages into MoldUDP64 datagrams with args.msgs_per_pkt
  // - Write a standard PCAP file with synthetic Ethernet/IP/UDP framing
  // - Derive timestamps from ITCH timestamp (ns since midnight)

  return 0;
}

