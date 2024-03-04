//
// Created by ccx on 2024/3/4.
//

#ifndef TINKER_SMART_PTR_H
#define TINKER_SMART_PTR_H

#include <algorithm>
namespace tinker {
template<typename T>
class smart_ptr {
 public:
  smart_ptr() = default;
  ~smart_ptr() { delete ptr_; }

  explicit smart_ptr(T *p) : ptr_(p) {}
  template<typename U>
  smart_ptr(smart_ptr<U> &&other) noexcept {
    ptr_ = other.release();
  }
  smart_ptr &operator=(smart_ptr rhs) {
    rhs.swap(*this);
    return *this;
  }

  T *get() { return ptr_; }
  T &operator*() { return *ptr_; }
  T *operator->() { return ptr_; }
  operator bool() const { return ptr_; }

 private:
  T *release() {
    T *p = ptr_;
    ptr_ = nullptr;
    return p;
  };
  void swap(smart_ptr &rhs) {
    using std::swap;
    swap(ptr_, rhs.ptr_);
  }
  T *ptr_{nullptr};
};

}

#endif // TINKER_SMART_PTR_H
