/*
  Ford-Fulkerson algorithm

  Max flow Problem

  Complexity: O(Ef)
    where E: number of edges in the graph
          f: maximum flow in the graph
*/

#include <iostream>
#include <vector>
#include <climits>

#define INF (INT_MAX/3)
#define debug(x) std::cout << #x << ": " << (x) << std::endl

struct edge { int to, cap, rev; };
typedef std::vector<std::vector<edge> > Graph;

void add_edge(Graph *G, int from, int to, int cap) {
  int rev1 = (*G)[to].size();
  int rev2 = (*G)[from].size();
  (*G)[from].push_back({to, cap, rev1});
  (*G)[to].push_back({from, 0, rev2});
}

// 増加パスを探す
int dfs(Graph *G, const int v, const int t, const int f, bool used[]) {
  if (v == t) return f;
  used[v] = true;
  for (size_t i = 0; i < (*G)[v].size(); ++i) {
    edge &e = (*G)[v][i];
    if (not used[e.to] and 0 < e.cap) {
      int d = dfs(G, e.to, t, std::min(f, e.cap), used);
      if (0 < d) {
        e.cap -= d;
        (*G)[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow_FF(Graph *G, const int s, const int t) {
  int V = G->size();
  int flow = 0;
  bool used[V];
  for (;;) {
    std::fill(used, used + V, 0);
    int f = dfs(G, s, t, INF, used);
    if (f == 0) return flow;
    flow += f;
  }
}

int main() {
  int s = 0,
    t = 4;
  Graph G(5);
  add_edge(&G, s, 1, 10);
  add_edge(&G, s, 2, 2);
  add_edge(&G, 1, 2, 6);
  add_edge(&G, 1, 3, 6);
  add_edge(&G, 2, t, 5);
  add_edge(&G, 3, 2, 3);
  add_edge(&G, 3, t, 8);

  debug(max_flow_FF(&G, s, t) == 11);
  return 0;
}
