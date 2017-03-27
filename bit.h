#pragma once

/*
  Binary Indexed Tree

  インデックスは1から
 */
template <class T>
class BIT {
  T *ary;
  int n;

public:
  BIT(int n): ary(new int [n + 1]), n(n + 1) {}
  BIT(int n, T a[]): BIT(n) {
    for (int i = 1; i < this->n; ++i)
      this->add(i, a[i - 1]);
  }
  ~BIT() { delete [] this->ary; }

  void add(int i, int x) {
    while (i < this->n) {
      ary[i] += x;
      i += i & -i;
    }
  }

  // インデックスがi番目までの値の総和
  int sum(int i) const {
    int s = 0;
    while (0 < i) {
      s += this->ary[i];
      i -= i & -i;
    }
    return s;
  }

};
