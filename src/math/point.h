#ifndef POINT_H
#define POINT_H

template <typename T, int D>
class Point {
 public:
  Point(T x, T y, T z);

 private:
  int point[D];
};

#endif
