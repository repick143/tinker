//
// Created by ccx on 2024/3/1.
//
#include "fmt/core.h"
#include "gtest/gtest.h"

TEST(grammar, decltype_case) {
  fmt::print("the magic mode is {}", 143);
  auto v = 123;
  static_assert(std::is_same_v<decltype(v), int>);
  static_assert(std::is_same_v<decltype(v), int32_t>);
}
