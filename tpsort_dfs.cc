/*
  Topological Sort

  Depth First Search Version
*/

#include "tpsort.h"

void visit(const Graph &G, int v, bool visited[], int **last) {
  if (visited[v]) return;
  visited[v] = true;
  for (auto e: G[v])
    visit(G, e, visited, last);
  *(--(*last)) = v;
}

// グラフに循環がある場合にそれをエラーとして検出することはできない
std::size_t tpsort_dfs(const Graph &G, int res[]) {
  int V = G.size();
  int *last = res + V;
  bool visited[V] = {0};
  for (int i = 0; i < V; ++i)
    visit(G, i, visited, &last);
  return V - *last;
}
