//
// Created by ccx on 2024/3/1.
//
#include <string>
#include <memory>
#include <random>
#include "array"

#include "glog/logging.h"
#include "exercise/tp.h"
#include "fmt/core.h"
#include "fmt/format.h"
#include "gtest/gtest.h"
#include "exercise/unique_ptr.h"
#include "exercise/shared_ptr.h"
#include "exercise/Shape.h"
#include "exercise/Circle.h"
#include "exercise/LruCache.h"
#include "exercise/sort.h"

namespace tinker {

class SortCase {
 public:
  std::unique_ptr<int64_t> arr{nullptr};
  int32_t len{0};

  SortCase() = default;
  explicit SortCase(int32_t len) : len(len) {
    arr = std::unique_ptr<int64_t>(new int64_t[len]);
  }
  SortCase(const SortCase &other) = delete;
  SortCase(SortCase &&other) noexcept {
    len = other.len;
    arr = std::move(other.arr);
  }
  SortCase &operator=(SortCase rhs) {
    rhs.swap(*this);
    return *this;
  }
  SortCase DeepCopy() const {
    SortCase ret;
    if (len == 0 || arr == nullptr) return ret;
    ret.len = len;
    ret.arr.reset(new int64_t[len]);
    memcpy(ret.arr.get(), arr.get(), sizeof(int64_t) * len);
    return ret;
  }

  bool DeepEqual(const SortCase &other) const {
    if (len != other.len) return false;
    if (arr == other.arr) return true;
    if (arr == nullptr || other.arr == nullptr) return false;
    auto i = memcmp(arr.get(), other.arr.get(), sizeof(int64_t) * len);
    if (i == 0) return true;
    return false;
  }

  std::string DebugString() const {
    if (arr == nullptr) {
      return fmt::format("len={},arr=nullptr", len);
    }
    return fmt::format("len={},arr={}", len, fmt::join(arr.get(), arr.get() + len, ","));
  }
 private:
  void swap(SortCase &other) {
    std::swap(arr, other.arr);
    std::swap(len, other.len);
  }
};

int32_t get_random_int(int32_t begin, int32_t end) {
  static std::random_device rd;
  static std::default_random_engine eng(rd());
  std::uniform_int_distribution<int32_t> distr(begin, end);
  return distr(eng);
}

SortCase gen_sort_case() {
  auto size = get_random_int(1, 100);
  SortCase ret(size);
  for (auto i = 0; i < size - 1; i++) {
    *(ret.arr.get() + i) = get_random_int(1, 100);
  }
  return ret;
}

std::vector<SortCase> gen_sort_case_batch(int32_t size) {
  std::vector<SortCase> ret;
  ret.reserve(size);
  for (auto i = 0; i < size; i++) {
    ret.emplace_back(gen_sort_case());
  }
  return ret;
}

TEST(exercise, BubbleSort) {
  auto sort_check = [](const SortCase &sort_case, std::function<void(int64_t[], int32_t)> f) {
    auto tmp = sort_case.DeepCopy();
    LOG(INFO) << "ori" << sort_case.DebugString();
    f(sort_case.arr.get(), sort_case.len);
    std::sort(tmp.arr.get(), tmp.arr.get() + tmp.len);
    EXPECT_TRUE(tmp.DeepEqual(sort_case)) << "";
    LOG(INFO) << "cus" << sort_case.DebugString();
    LOG(INFO) << "std" << tmp.DebugString();
  };
  for (const auto &cs : gen_sort_case_batch(1000)) {
    sort_check(cs, BubbleSort);
  }
  for (const auto &cs : gen_sort_case_batch(1000)) {
    sort_check(cs, InsertionSort);
  }
  for (const auto &cs : gen_sort_case_batch(1000)) {
    sort_check(cs, MergeSort);
  }
  fmt::println("ok");
}

TEST(exercise, LruCache) {
  LruCache lru(2);
  lru.put(1, 1);
  lru.put(2, 2);
  EXPECT_EQ(1, lru.get(1));
  EXPECT_EQ(2, lru.get(2));
  lru.put(1, 1);
  lru.put(1, 1);
  lru.put(1, 1);
  lru.put(3, 3);
  lru.put(3, 3);
  lru.put(3, 3);
  EXPECT_EQ(1, lru.get(1));
  EXPECT_EQ(-1, lru.get(2));
  EXPECT_EQ(3, lru.get(3));
  lru.put(1, 11);
  EXPECT_EQ(11, lru.get(1));
}

TEST(grammar, decltype_case) {
  fmt::print("the magic mode is {}", 143);
  [[maybe_unused]] auto v = 123;
  static_assert(std::is_same_v<decltype(v), int>);
  static_assert(std::is_same_v<decltype(v), int32_t>);
}

TEST(exercise, unique_ptr) {
  {
    unique_ptr<Shape> shape(new Circle());
//    unique_ptr<Shape> p1(shape);
    unique_ptr<Shape> p2(std::move(shape));

  }
  {
    unique_ptr<Circle> shape(new Circle(2));
    unique_ptr<Shape> p1;
//    p1 = shape;
    p1 = std::move(shape);
    unique_ptr<Shape> p2(std::move(p1));
    ASSERT_FALSE(p1);
    ASSERT_TRUE(p2);
    LOG(INFO) << "p2.value=" << p2->ToString();
  }
}

TEST(exercise, shared_ptr) {
  shared_ptr<Circle> shape(new Circle());
  shared_ptr<Shape> p1(shape);
  EXPECT_TRUE(shape);
  EXPECT_TRUE(p1);
  EXPECT_EQ(2, shape.counter());
  EXPECT_EQ(2, p1.counter());
  shared_ptr<Shape> p2 = shape;
  EXPECT_EQ(3, shape.counter());
  EXPECT_EQ(3, p1.counter());
  EXPECT_EQ(3, p2.counter());
  shared_ptr<Shape> p3 = std::move(p2);
  EXPECT_EQ(3, shape.counter());
  EXPECT_EQ(3, p1.counter());
  EXPECT_EQ(0, p2.counter());
  EXPECT_EQ(3, p3.counter());
  shared_ptr<Shape> p4(std::move(p3));
  EXPECT_EQ(3, shape.counter());
  EXPECT_EQ(3, p1.counter());
  EXPECT_EQ(0, p2.counter());
  EXPECT_EQ(0, p3.counter());
  EXPECT_EQ(3, p4.counter());

  std::array<int, 5> arr1{};
  fmt::println("arr={}", fmt::join(arr1.begin(), arr1.end(), ","));
  std::array<int, 5> arr2;
  arr2.fill(0);
  fmt::println("arr={}", fmt::join(arr2.begin(), arr2.end(), ","));

  static_assert(has_reserve_v<std::vector<int>>, "vector has reserve");
  doSomething(123);
  doSomething(1.1);
//  doSomething(std::string(123));
}
}


