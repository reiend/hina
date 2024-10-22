#include "./point.h"

template <typename T, int D>
Point<T, D>::Point(T x, T y, T z) {
  this->point[0] = x;
  this->point[1] = y;
  this->point[2] = z;
}
