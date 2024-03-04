//
// Created by ccx on 2024/3/4.
//

#ifndef TINKER_EXERCISE_SHARED_PTR_H_
#define TINKER_EXERCISE_SHARED_PTR_H_
#include <algorithm>
#include "fmt/core.h"
#include "glog/logging.h"

namespace tinker {

class shared_counter {
 public:
  shared_counter() = default;
  void add_count() { ++cnt_; }
  int delete_count() {
    return --cnt_;
  }
  int get_count() const {
    return cnt_;
  }
 private:
  int cnt_{1};
};

template<typename T>
class shared_ptr {
 public:
  shared_ptr() = default;
  explicit shared_ptr(T *ptr) : ptr_(ptr) {
    LOG(INFO) << fmt::format("construct T *ptr, ptr={}", static_cast<void *>(ptr_));
    if (ptr_) counter_ = new shared_counter;
  }
  ~shared_ptr() {
    if (ptr_ && !counter_->delete_count()) {
      LOG(INFO) << fmt::format("deconstruct ptr={}", static_cast<void *>(ptr_));
      delete ptr_;
      delete counter_;
    }
  }

  template<typename U>
  friend
  class shared_ptr;

  template<class U>
  shared_ptr(shared_ptr<U> &other) {
    ptr_ = other.ptr_;
    if (ptr_) {
      other.counter_->add_count();
      counter_ = other.counter_;
    }
    LOG(INFO) << fmt::format("copy construct v={}/{}", static_cast<void *>(ptr_), other.counter_->get_count());
  }

  template<class U>
  shared_ptr(shared_ptr<U> &&other) {
    LOG(INFO)
        << fmt::format("move construct counter={}/{}", static_cast<void *>(other.ptr_), other.counter_->get_count());
    ptr_ = other.ptr_;
    if (ptr_) {
      counter_ = other.counter_;
      other.counter_ = nullptr;
      other.ptr_ = nullptr;
    }
  }

  shared_ptr &operator=(shared_ptr rhs) {
    rhs.swap(*this);
    return *this;
  }

  shared_ptr &operator*() {
    return *ptr_;
  }
  shared_ptr *operator->() {
    return ptr_;
  }
  operator bool() const {
    return ptr_;
  }

  int counter() {
    if (counter_) return counter_->get_count();
    return 0;
  }

  void swap(shared_ptr &rhs) {
    using std::swap;
    swap(ptr_, rhs.ptr_);
    swap(counter_, rhs.counter_);
  }

 private:
  T *ptr_{nullptr};
  shared_counter *counter_{nullptr};
};

}

#endif //TINKER_EXERCISE_SHARED_PTR_H_
