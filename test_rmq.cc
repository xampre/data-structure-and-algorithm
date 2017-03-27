#include <iostream>
#include <vector>
#include "rmq.h"

#define debug(x) cout << #x << ": " << (x) << endl

using namespace std;

int main() {
  int n = 8;
  int inits[n] = {5, 3, 7, 9, 6, 4, 1, 2};
  RMQ<int> r(n);
  for (int i = 0; i < n; ++i)
    r.update(i, inits[i]);

  debug(r.min(0, 7) == 1);
  debug(r.min(0, 5) == 3);
  return 0;
}
