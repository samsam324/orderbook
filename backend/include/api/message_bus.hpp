// Owner: ROLE 5 (UI + Backend WS API)
#pragma once

#include <cstddef>
#include <cstdint>
#include <deque>
#include <mutex>
#include <optional>
#include <string>

namespace md::api {

// Bounded message bus for UI-bound payloads.
// Skeleton uses std::string messages containing JSON text.

// Requirements:
// - Bounded memory, drop policy with counters
// - Multi-producer, multi-consumer (engine + reporter + book)
class MessageBus final {
public:
  explicit MessageBus(std::size_t capacity) : capacity_(capacity) {}

  bool try_publish(std::string msg) {
    std::lock_guard<std::mutex> lk(mu_);
    if (q_.size() >= capacity_) return false;
    q_.push_back(std::move(msg));
    return true;
  }

  std::optional<std::string> try_consume() {
    std::lock_guard<std::mutex> lk(mu_);
    if (q_.empty()) return std::nullopt;
    std::string v = std::move(q_.front());
    q_.pop_front();
    return v;
  }

  std::size_t size_approx() const {
    std::lock_guard<std::mutex> lk(mu_);
    return q_.size();
  }

private:
  const std::size_t capacity_;
  mutable std::mutex mu_;
  std::deque<std::string> q_;
};

} // namespace md::api

