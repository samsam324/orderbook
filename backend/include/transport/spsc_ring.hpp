// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "transport/ievent_queue.hpp"

namespace md::transport {

// Skeleton SPSC ring buffer.

// Intended properties (later implementation):
// - Single producer, single consumer
// - Bounded capacity (power of two)
// - Lock free using atomics with careful memory ordering

// What this current does (aka we still need to implement this)
// - Provides the same API but currently uses a simple vector and indices without atomics
class SpscRing final : public IEventQueue {
public:
  explicit SpscRing(std::size_t capacity_pow2);

  bool try_push(const core::EventFrame& ev) override;
  bool try_pop(core::EventFrame& out) override;
  std::size_t size_approx() const override;

  std::size_t capacity() const noexcept { return capacity_; }

private:
  std::size_t capacity_{0};
  std::vector<core::EventFrame> buf_{};
  std::size_t head_{0};
  std::size_t tail_{0};
  std::size_t size_{0};
};

} // namespace md::transport

