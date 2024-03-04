//
// Created by ccx on 2024/3/4.
//

#ifndef TINKER_EXERCISE_CIRCLE_H_
#define TINKER_EXERCISE_CIRCLE_H_

#include <string>

#include "exercise/Shape.h"

namespace tinker {

class Circle final : public Shape {
 public:
  explicit Circle(int diam) : diam_(diam) {};
  Circle() = default;
  ~Circle() override = default;

  std::string ToString() override;
 private:
  int diam_{0};
};
}

#endif //TINKER_EXERCISE_CIRCLE_H_
