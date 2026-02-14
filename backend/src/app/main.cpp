// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)

#include "app/engine.hpp"
#include "app/modes.hpp"
#include "core/config.hpp"
#include "core/logging.hpp"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

namespace {

void print_usage() {
  std::cerr
    << "md_engine (skeleton)\n"
    << "Usage:\n"
    << "  md_engine --input <pcap_replay|itch_binfile_replay|udp_live|sim_udp>\n"
    << "            [--pcap <file.pcap>] [--itchbin <file>]\n"
    << "            --symbol <SYM> --queue <mutex|ring> --threads <single_thread|two_thread>\n"
    << "            --ws_port <PORT> --speed <N> [--duration_ms <MS>]\n";
}

bool parse_args(int argc, char** argv, md::core::Config& cfg) {
  for (int i = 1; i < argc; ++i) {
    const std::string a = argv[i];
    auto need_val = [&](const char* flag) -> const char* {
      if (i + 1 >= argc) {
        std::cerr << "Missing value for " << flag << "\n";
        return nullptr;
      }
      return argv[++i];
    };

    if (a == "--input") {
      const char* v = need_val("--input"); if (!v) return false;
      cfg.input = v;
    } else if (a == "--pcap") {
      const char* v = need_val("--pcap"); if (!v) return false;
      cfg.pcap = v;
    } else if (a == "--itchbin") {
      const char* v = need_val("--itchbin"); if (!v) return false;
      cfg.itchbin = v;
    } else if (a == "--symbol") {
      const char* v = need_val("--symbol"); if (!v) return false;
      cfg.symbol = v;
    } else if (a == "--queue") {
      const char* v = need_val("--queue"); if (!v) return false;
      cfg.queue = v;
    } else if (a == "--threads") {
      const char* v = need_val("--threads"); if (!v) return false;
      cfg.threads = v;
    } else if (a == "--ws_port") {
      const char* v = need_val("--ws_port"); if (!v) return false;
      cfg.ws_port = static_cast<std::uint16_t>(std::atoi(v));
    } else if (a == "--speed") {
      const char* v = need_val("--speed"); if (!v) return false;
      cfg.speed = std::atoi(v);
    } else if (a == "--duration_ms") {
      const char* v = need_val("--duration_ms"); if (!v) return false;
      cfg.duration_ms = static_cast<std::uint64_t>(std::strtoull(v, nullptr, 10));
    } else if (a == "--help" || a == "-h") {
      return false;
    } else {
      std::cerr << "Unknown arg: " << a << "\n";
      return false;
    }
  }
  return true;
}

} // namespace

int main(int argc, char** argv) {
  md::core::Config cfg;
  if (!parse_args(argc, argv, cfg)) {
    print_usage();
    return 2;
  }

  md::app::Engine::Config ecfg;
  ecfg.modes.input_mode = md::app::parse_input_mode(cfg.input);
  ecfg.modes.queue_mode = md::app::parse_queue_mode(cfg.queue);
  ecfg.modes.thread_mode = md::app::parse_thread_mode(cfg.threads);
  ecfg.symbol = cfg.symbol;
  ecfg.pcap_path = cfg.pcap;
  ecfg.itchbin_path = cfg.itchbin;
  ecfg.ws_port = cfg.ws_port;
  ecfg.speed = cfg.speed;

  md::app::Engine engine(ecfg);
  if (!engine.start()) {
    MD_LOG_ERROR("engine failed to start");
    return 1;
  }

  // For now run for duration_ms if provided, else run until killed
  if (cfg.duration_ms > 0) {
    std::thread t([&] { engine.run(); });
    std::this_thread::sleep_for(std::chrono::milliseconds(cfg.duration_ms));
    engine.stop();
    t.join();
  } else {
    engine.run();
  }

  return 0;
}

