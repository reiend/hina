#include "./point.h"

template <typename T, int D>
Point<T, D>::Point(T x, T y, T z) {
  static_assert(D == 3, "Point<T, D> initialization failed: D must be 3");

  this->point[0] = x;
  this->point[1] = y;
  this->point[2] = z;
}
