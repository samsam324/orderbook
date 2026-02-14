// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)
#pragma once

#include <cstddef>
#include <cstdint>
#include <deque>
#include <mutex>

#include "transport/ievent_queue.hpp"

namespace md::transport {

// Baseline bounded queue: mutex + deque
// This is intentionally simple and correct. performance will comes later
class MutexQueue final : public IEventQueue {
public:
  explicit MutexQueue(std::size_t capacity);

  bool try_push(const core::EventFrame& ev) override;
  bool try_pop(core::EventFrame& out) override;
  std::size_t size_approx() const override;

private:
  const std::size_t capacity_;
  mutable std::mutex mu_;
  std::deque<core::EventFrame> q_;
};

} // namespace md::transport

