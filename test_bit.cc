#include <iostream>
#include <vector>
#include "bit.h"

#define debug(x) cout << #x << ": " << (x) << endl

typedef long long LL;

using namespace std;

int main() {
  int n = 8;
  int a[] = {5, 3, 7, 9, 6, 4, 1, 2};
  BIT<int> b(n, a);
  debug(b.sum(5) == 30);
  b.add(3, 10);
  debug(b.sum(2) == 8);
  debug(b.sum(4) == 34);
  return 0;
}
