// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)

#include "transport/spsc_ring.hpp"

namespace md::transport {

SpscRing::SpscRing(std::size_t capacity_pow2) : capacity_(capacity_pow2), buf_(capacity_pow2) {
  // TODO(ROLE3): validate power of two and non zero.
}

bool SpscRing::try_push(const core::EventFrame& ev) {
  // TODO(ROLE3): lock free push using atomics. Skeleton uses size_
  if (size_ >= capacity_) return false;
  buf_[tail_] = ev;
  tail_ = (tail_ + 1) % capacity_;
  size_++;
  return true;
}

bool SpscRing::try_pop(core::EventFrame& out) {
  // TODO(ROLE3): lock free pop using atomics
  if (size_ == 0) return false;
  out = buf_[head_];
  head_ = (head_ + 1) % capacity_;
  size_--;
  return true;
}

std::size_t SpscRing::size_approx() const {
  return size_;
}

} // namespace md::transport

