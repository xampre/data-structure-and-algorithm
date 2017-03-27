#include <iostream>
#include <vector>
#include <algorithm>
#include "uft.h"

#define debug(x) cout << #x << ": " << (x) << endl

struct edge { int u, v, cost; };

bool comp(const edge &e1, const edge &e2) {
  return e1.cost < e2.cost;
}

int kruskal(const int V, std::vector<edge> *es) {
  UFT u(V);
  std::sort(es->begin(), es->end(), comp);
  int res = 0;
  for (size_t i = 0; i < es->size(); ++i) {
    const edge &e = es->at(i);
    if (not u.same(e.u, e.v)) {
      u.unite(e.u, e.v);
      res += e.cost;
    }
  }
  return res;
}

int main() {
  using namespace std;
  int V = 7;
  vector<edge> es = {
    {0, 1, 7}, {0, 3, 5}, {1, 2, 8}, {1, 3, 9},
    {1, 4, 7}, {2, 4, 5}, {3, 4, 15}, {3, 5, 6},
    {4, 5, 8}, {4, 6, 9}, {5, 6, 11}
  };

  debug(kruskal(V, &es) == 39);
  return 0;
}
