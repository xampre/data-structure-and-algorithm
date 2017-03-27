/*
  Topological Sort
*/

#include "tpsort.h"
#include <queue>

// グラフGのトポロジカルソートされた頂点をaに格納。
// 戻り値はaの要素数で、この値がGの頂点数と一致しない場合、Gはトポロジカルソート出来ない。
std::size_t tpsort_Kahn(Graph *G, int res[]) {
  std::size_t V = G->size();
  int in_counts[V] = {0};

  for (std::size_t i = 0; i < V; ++i) {
    for (std::size_t j = 0; j < (*G)[i].size(); ++j) {
      ++in_counts[(*G)[i][j]];
    }
  }

  std::queue<int> q;
  for (std::size_t i = 0; i < V; ++i)
    if (in_counts[i] == 0)
      q.push(i);

  std::size_t idx = 0;
  while (not q.empty()) {
    int v = q.front(); q.pop();
    res[idx++] = v;
    std::vector<int> &vs = (*G)[v];
    for (int i = vs.size() - 1; 0 <= i; --i) {
      int m = vs[i]; vs.pop_back();
      --in_counts[m];
      if (in_counts[m] <= 0)
        q.push(m);
    }
  }
  return idx;
}
