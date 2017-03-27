#include <iostream>
#include <vector>
#include <algorithm>

#define debug(x) cout << #x << ": " << (x) << endl

typedef std::vector<int> VI;
typedef std::vector<VI> Graph;

// 増加パスを探す
bool dfs(const Graph &G, int v, bool used[], int match[]) {
  used[v] = true;
  for (size_t i = 0; i < G[v].size(); ++i) {
    int u = G[v][i],
      w = match[u];
    if (w < 0 or (not used[w] and dfs(G, w, used, match))) {
      match[v] = u;
      match[u] = v;
      return true;
    }
  }
  return false;
}

// 2部グラフの最大マッチングを返す
int bipartite_matching(const Graph &G) {
  int res = 0;
  int V = G.size();
  int match[V];
  bool used[V];
  std::fill(match, match + V, -1);

  for (int v = 0; v < V; ++v) {
    if (match[v] < 0) {
      std::fill(used, used + V, 0);
      if (dfs(G, v, used, match))
        res++;
    }
  }
  return res;
}

void add_edge(Graph &G, int u, int v) {
  G[u].push_back(v);
  G[v].push_back(u);
}

int main() {
  using namespace std;

  int N = 6;
  int K = 4;
  VI edges[] = {
    VI{3+N, 0+N},
    VI{2+N},
    VI{0+N, 3+N},
    VI{1+N},
    VI{1+N, 2+N},
    VI{2+N}
  };

  Graph G(K + N);
  for (int i = 0; i < N; ++i)
    for (size_t j = 0; j < edges[i].size(); ++j)
      add_edge(G, i, edges[i][j]);

  debug(bipartite_matching(G) == 4);
  return 0;
}
