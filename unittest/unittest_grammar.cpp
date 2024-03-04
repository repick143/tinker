//
// Created by ccx on 2024/3/1.
//
#include <string>

#include "glog/logging.h"
#include "fmt/core.h"
#include "gtest/gtest.h"
#include "exercise/unique_ptr.h"
#include "exercise/shared_ptr.h"
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
}
}


