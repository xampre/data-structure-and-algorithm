/*
  Dinic's algorighm

  Maximum flow problem

  Complexity: O(V^2E)
    where V: number of vertices in the graph
          E: number of edges in the graph
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

#define debug(x) std::cout << #x << ": " << (x) << std::endl

struct edge { int to, cap, rev; };
typedef std::vector<std::vector<edge> > Graph;

const int INF = INT_MAX / 3;

void add_edge(Graph *G, int from, int to, int cap) {
  int rev1 = (*G)[to].size();
  int rev2 = (*G)[from].size();
  (*G)[from].push_back({to, cap, rev1});
  (*G)[to].push_back({from, 0, rev2});
}

// sからの最短経路を level[] にセット
void bfs(const Graph &G, const int s, int level[]) {
  std::queue<int> q;
  std::fill(level, level + G.size(), -1);
  level[s] = 0;
  q.push(s);
  while (not q.empty()) {
    int v = q.front(); q.pop();
    for (size_t i = 0; i < G[v].size(); ++i) {
      const edge &e = G[v][i];
      if (0 < e.cap and level[e.to] < 0) {
        level[e.to] = level[v] + 1;
        q.push(e.to);
      }
    }
  }
}

// 増加パスを探す
int dfs(Graph *G, int v, int t, int f, int level[], size_t iter[]) {
  if (v == t) return f;
  for (size_t &i = iter[v]; i < (*G)[v].size(); ++i) {
    edge &e = (*G)[v][i];
    if (0 < e.cap and level[v] < level[e.to]) {
      int d = dfs(G, e.to, t, std::min(f, e.cap), level, iter);
      if (0 < d) {
        e.cap -= d;
        (*G)[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int max_flow_dinic(Graph *G, int s, int t) {
  int V = G->size();
  int level[V]; // sからの最短距離
  size_t iter[V]; // どの辺まで調べたのか
  int flow = 0;
  for (;;) {
    bfs(*G, s, level);
    if (level[t] < 0) return flow;
    std::fill(iter, iter + V, 0);
    int f;
    while (0 < (f = dfs(G, s, t, INF, level, iter))) {
      flow += f;
    }
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

  debug(max_flow_dinic(&G, s, t) == 11);
  return 0;
}
