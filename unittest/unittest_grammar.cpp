//
// Created by ccx on 2024/3/1.
//
#include <string>

#include "glog/logging.h"
#include "fmt/core.h"
#include "gtest/gtest.h"
#include "exercise/unique_ptr.h"
#include "exercise/Shape.h"
#include "exercise/Circle.h"
#include <memory>

namespace tinker {
TEST(grammar, decltype_case) {
  fmt::print("the magic mode is {}", 143);
  [[maybe_unused]] auto v = 123;
  static_assert(std::is_same_v<decltype(v), int>);
  static_assert(std::is_same_v<decltype(v), int32_t>);
}

TEST(exercise, unique_ptr) {
  std::unique_ptr<Shape> v;
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
}

