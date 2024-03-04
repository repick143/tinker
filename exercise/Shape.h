//
// Created by ccx on 2024/3/4.
//

#ifndef TINKER_EXERCISE_SHAPE_H_
#define TINKER_EXERCISE_SHAPE_H_
namespace tinker {

class Shape {
 public:
  virtual ~Shape() = default;
  virtual std::string ToString() = 0;
};

}
#endif //TINKER_EXERCISE_SHAPE_H_
