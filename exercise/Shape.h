//
// Created by ccx on 2024/3/4.
//

#ifndef TINKER_EXERCISE_SHAPE_H_
#define TINKER_EXERCISE_SHAPE_H_

class Shape {
 public:
  Shape() = default;
  virtual ~Shape() = default;
  int GetLen() const;
  void SetLen(int len);
  int GetHeight() const;
  void SetHeight(int height);
  Shape(int len, int height);

 private:
  int len_{0};
  int height_{0};
};

#endif //TINKER_EXERCISE_SHAPE_H_
