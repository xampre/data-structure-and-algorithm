#include "tpsort.h"
#include <iostream>
#include <algorithm>
#include <set>

#define debug(x) std::cout << #x << ": " << (x) << std::endl

using namespace std;

typedef vector<int> VI;

int main() {
  const int V = 8;
  Graph G(V);
  Graph G_copy;
  set<vector<int> > anss = {
    VI{3, 2, 1, 7, 4, 0, 5, 6},
    VI{1, 2, 3, 4, 7, 0, 5, 6},
    VI{1, 2, 3, 7, 4, 6, 0, 5},
    VI{1, 3, 4, 2, 7, 6, 0, 5},
    VI{2, 6, 1, 4, 7, 6, 5, 0},
    VI{3, 2, 7, 1, 6, 4, 5, 0},
    VI{3, 2, 7, 0, 1, 4, 5, 6},
  };

  G[1].push_back(4);
  G[1].push_back(6);
  G[2].push_back(7);
  G[3].push_back(4);
  G[3].push_back(7);
  G[4].push_back(5);
  G[7].push_back(0);
  G[7].push_back(5);
  G[7].push_back(6);

  int res[V];
  tpsort_dfs(G, res);
  debug(anss.find(std::vector<int>(res, res + V)) != anss.end());

  G_copy = G;
  fill(res, res + V, 0);
  tpsort_Kahn(&G_copy, res);
  debug(anss.find(std::vector<int>(res, res + V)) != anss.end());

  return 0;
}

