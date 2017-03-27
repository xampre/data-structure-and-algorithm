#pragma once

#include <limits>
#include <algorithm>

#define LEFT(k) (2*(k) + 1)
#define RIGHT(k) (2*(k) + 2)
#define MID(l, r) (((l) + (r)) / 2)
#define DEFAULT_INF std::numeric_limits<T>::max() / 3

/*
  Range Minimum Query
*/
template<typename T>
class RMQ {
  T inf;
  T *dat;
  size_t n;

public:

  RMQ(size_t N, T inf = DEFAULT_INF): inf(inf) {
    size_t n = 1;
    while (n < N) n *= 2;

    this->n = n;
    size_t size = 2 * n - 1;
    this->dat = new T [size];

    for (size_t i = 0; i < size; ++i)
      this->dat[i] = inf;
  }

  template<class InputIterator>
  RMQ(InputIterator first, InputIterator last, T inf = DEFAULT_INF)
    : RMQ(last - first, inf) {
    for (int i = 0; i < last - first; ++i)
      update(i, *(first + i));
  }

  ~RMQ() { delete [] dat; }

  // minimum value of [a, b)
  T min(size_t a, size_t b) const { return this->min(a, b, 0, 0, n); }

  T min(size_t a, size_t b, size_t k, size_t l, size_t r) const {
    if (r <= a or b <= l) // [a, b) と [l, r) が交差しない
      return inf;
    if (a <= l and r <= b) return dat[k];
    return std::min(this->min(a, b, LEFT(k), l, MID(l, r)),
                    this->min(a, b, RIGHT(k), MID(l, r), r));
  }

  // change kth value of dat to a
  void update(size_t k, T a) {
    k += this->n - 1;
    dat[k] = a;

    // 下から上
    while (0 < k) {
      k = (k - 1) / 2;
      dat[k] = std::min(dat[LEFT(k)], dat[RIGHT(k)]);
    }
  }
};
