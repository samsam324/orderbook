// Owner: Integration (tests)
// Fully shared between roles

#include "app/engine.hpp"

#include <cassert>
#include <chrono>
#include <thread>

int main() {
  md::app::Engine::Config cfg;
  cfg.ws_port = 0; // bind ephemeral for tests
  cfg.symbol = "AAPL";

  md::app::Engine engine(cfg);
  assert(engine.start());

  std::thread t([&] { engine.run(); });
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  engine.stop();
  t.join();

  // Skeleton increments packets_read in its loop
  assert(engine.counters().packets_read.load() > 0);
  return 0;
}

