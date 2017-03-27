#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
using namespace std;

double EPS = numeric_limits<double>::epsilon();

// 誤差を考慮した足し算
double add(double a, double b) {
  return (abs(a + b) < EPS * (abs(a) + abs(b))) ? 0 : a + b;
}

struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  Point operator + (Point p) const { return Point(add(x, p.x), add(y, p.y)); }
  Point operator - (Point p) const { return Point(add(x, -p.x), add(y, -p.y)); }
  Point operator * (double d) const { return Point(x * d, y * d); }

  static double det(const Point &p, const Point &q) {
    return add(p.x * q.y, -p.y * q.x);
  }

  double det(const Point &p) const { return Point::det(*this, p); }
};

bool cmp_x(const Point &p, const Point &q) {
  return (p.x == q.x) ? p.y < q.y : p.x < q.x;
}

vector<Point> convex_hull_graham_scan(Point *ps, int n) {
  sort(ps, ps + n, cmp_x);
  int k = 0;
  vector<Point> qs(2*n);

  // 下側
  for (int i = 0; i < n; ++i) {
    while (1 < k and (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0)
      k--;
    qs[k++] = ps[i];
  }
  // 上側
  for (int i = n - 2, t = k; 0 <= i; --i) {
    while (t < k and (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0)
      k--;
    qs[k++] = ps[i];
  }
  qs.resize(k - 1);
  return qs;
}

int main() {
  return 0;
}
