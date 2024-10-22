#ifndef POINT_H
#define POINT_H

template <typename T, int D>
class Point {
 public:
  int point[D];

  Point(T x, T y);
  Point(T x, T y, T z);
};

#endif
