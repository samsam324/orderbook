// Owner: ROLE 3 (Pipeline/Concurrency/Modes/Metrics)

#include "transport/mutex_queue.hpp"

namespace md::transport {

MutexQueue::MutexQueue(std::size_t capacity) : capacity_(capacity) {}

bool MutexQueue::try_push(const core::EventFrame& ev) {
  std::lock_guard<std::mutex> lk(mu_);
  if (q_.size() >= capacity_) return false;
  q_.push_back(ev);
  return true;
}

bool MutexQueue::try_pop(core::EventFrame& out) {
  std::lock_guard<std::mutex> lk(mu_);
  if (q_.empty()) return false;
  out = q_.front();
  q_.pop_front();
  return true;
}

std::size_t MutexQueue::size_approx() const {
  std::lock_guard<std::mutex> lk(mu_);
  return q_.size();
}

} // namespace md::transport

