#include <iostream>
#include <limits>
#include <cmath>

double EPS = std::numeric_limits<double>::epsilon();

// 誤差を考慮した足し算
double add(double a, double b) {
  return (std::abs(a + b) < EPS * (std::abs(a) + std::abs(b))) ? 0 : a + b;
}

struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  Point operator + (Point p) const { return Point(add(x, p.x), add(y, p.y)); }
  Point operator - (Point p) const { return Point(add(x, -p.x), add(y, -p.y)); }
  Point operator * (double d) const { return Point(x * d, y * d); }

  static double dot(const Point &p, const Point &q) {
    return add(p.x * q.x, p.y * q.y);
  }

  static double det(const Point &p, const Point &q) {
    return add(p.x * q.y, -p.y * q.x);
  }

  static double dist(const Point &p, const Point &q) {
    return (p - q).dot(p - q);
  }

  double dot(const Point &p) const { return Point::dot(*this, p); }
  double det(const Point &p) const { return Point::det(*this, p); }
  double dist(const Point &p) const { return Point::dist(*this, p); }
};

int main() {
  Point p1(1, 2);
  Point p2(2, 2);
  std::cout << (p1.dot(p2) == 6) << std::endl;
  std::cout << (p1.det(p2) == -2) << std::endl;
  return 0;
}
