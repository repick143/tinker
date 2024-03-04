//
// Created by ccx on 2024/3/4.
//

#ifndef TINKER_SMART_PTR_H
#define TINKER_SMART_PTR_H

#include <algorithm>

namespace tinker {

template<typename T>
class unique_ptr {
 public:
  unique_ptr() = default;
  explicit unique_ptr(T *p) : ptr_(p) {}
  ~unique_ptr() { delete ptr_; }

  unique_ptr(unique_ptr &other) = delete;
  unique_ptr &operator=(unique_ptr rhs) {
    rhs.swap(*this);
    return *this;
  }
  template<typename U>
  unique_ptr(unique_ptr<U> &&other) noexcept {
    ptr_ = other.release();
  }

  T *get() { return ptr_; }
  T &operator*() { return *ptr_; }
  T *operator->() { return ptr_; }
  operator bool() const { return ptr_; }

  T *release() {
    T *p = ptr_;
    ptr_ = nullptr;
    return p;
  };

 private:
  void swap(unique_ptr &rhs) {
    using std::swap;
    swap(ptr_, rhs.ptr_);
  }
  T *ptr_{nullptr};
};

}

#endif // TINKER_SMART_PTR_H
