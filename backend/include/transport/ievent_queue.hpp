// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <cstddef>
#include <cstdint>

#include "core/types.hpp"

namespace md::transport {

// Abstract queue interface used between decode and book stages
// Implementations:
// - MutexQueue (baseline correctness)
// - SpscRing (bounded, SPSC; intended lock free)
class IEventQueue {
public:
  virtual ~IEventQueue() = default;

  // Returns false if queue is full or drop occurred.
  virtual bool try_push(const core::EventFrame& ev) = 0;

  // Returns false if empty
  virtual bool try_pop(core::EventFrame& out) = 0;

  virtual std::size_t size_approx() const = 0;
};

} // namespace md::transport

