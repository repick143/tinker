//
// Created by ccx on 2024/3/4.
//

#include <string>
#include "Circle.h"
#include "fmt/core.h"

namespace tinker {
std::string Circle::ToString() {
  return fmt::format("Circle, diam={}", diam_);
}
}
