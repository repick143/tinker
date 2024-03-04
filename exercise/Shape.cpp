//
// Created by ccx on 2024/3/4.
//

#include "Shape.h"
Shape::Shape(int len, int height) : len_(len), height_(height) {}
int Shape::GetLen() const {
  return len_;
}
void Shape::SetLen(int len) {
  Shape::len_ = len;
}
int Shape::GetHeight() const {
  return height_;
}
void Shape::SetHeight(int height) {
  Shape::height_ = height;
}
