#include "uft.h"

UFT::UFT(const int N) {
  par = new int[N];
  rank = new int[N];

  for (int i = 0; i < N; ++i) {
    par[i] = i;
    rank[i] = 0;
  }
}

UFT::~UFT() {
  delete [] par;
  delete [] rank;
}

int UFT::find(int x) {
  return par[x] == x ? x : par[x] = find(par[x]);
}

void UFT::unite(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return;

  if (rank[x] < rank[y]) {
    par[x] = y;
  } else {
    par[y] = x;
    if (rank[x] == rank[y])
      ++rank[x];
  }
}

bool UFT::same(int x, int y) {
  return find(x) == find(y);
}

