//
// Created by ccx on 2024/3/1.
//
#include "fmt/core.h"
#include "gtest/gtest.h"
#include "exercise/smart_ptr.h"
#include "exercise/Shape.h"
#include "exercise/Circle.h"
#include <string>

namespace tinker {
TEST(grammar, decltype_case) {
  fmt::print("the magic mode is {}", 143);
  auto v = 123;
  static_assert(std::is_same_v<decltype(v), int>);
  static_assert(std::is_same_v<decltype(v), int32_t>);
}

TEST(exercise, smart_ptr) {
  {
    smart_ptr<Shape> shape(new Circle());
//  smart_ptr<Shape> p1(shape);
    smart_ptr<Shape> p1(std::move(shape));

  }
  {
    smart_ptr<Shape> shape(new Circle(2));
    smart_ptr<Shape> p1;
//    p1 = shape;
    p1 = std::move(shape);
    smart_ptr<Shape> p2(std::move(p1));
    ASSERT_FALSE(p1);
    ASSERT_TRUE(p2);
  }
}
}

