#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int _total(int N, int y, int left, int down, int right) {
  if (N <= y) return 1;

  int mask = (1 << N) -1;
  int res = 0;
  int bitmap = mask & ~(left | down | right); // 置けるとことが1のビット

  while (bitmap) {
    int bit = -bitmap & bitmap; // 次に置くところが１のビット
    bitmap ^= bit;
    res += _total(N, y + 1, (left | bit) << 1,
                  (down | bit), (right | bit) >> 1);
  }
  return res;
}

int total(int N) {
  return _total(N, 0, 0, 0, 0);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " N ..." << endl;
    return 1;
  }

  cout << "N: total" << endl;
  for (int i = 1; i < argc; ++i) {
    int N = atoi(argv[i]);
    cout << N << ": " << total(N) << endl;
  }
  return 0;
}
