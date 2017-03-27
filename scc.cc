/*
  Strongly Connected Component
*/

#include <vector>
#include <algorithm>

typedef std::vector<std::vector<int> > Graph;

void add_edge(Graph *G, Graph *rG, int from, int to) {
  G->at(from).push_back(to);
  rG->at(to).push_back(from);
}

void dfs(const Graph &G, int v, bool used[], std::vector<int> *vs) {
  used[v] = true;
  for (int i = 0; i < G[v].size(); ++i) {
    if (not used[G[v][i]])
      dfs(G, G[v][i], used, vs);
  }
  vs->push_back(v);
}

void rdfs(const Graph &rG, int v, int k, bool used[], int cmp[]) {
  used[v] = true;
  cmp[v] = k;
  for (int i = 0; i < rG[v].size(); ++i) {
    if (not used[rG[v][i]])
      rdfs(rG, rG[v][i], k, used, cmp);
  }
}

/*
  強連結成分分解を求める。 戻り値は成分数。

  G: 強連結成分分解を求めるグラフ
  rG: Gの辺の向きを全て逆にしたグラフ
  cmp: G.size()の長さを持つ配列

  vをグラフの頂点に対応する数字とし、kを戻り値とした場合、cmp[v]の値が等しい頂点
  同士は同じ成分に属するようcmpに 0 ~ (k - 1) の値がセットされる。また、i < jを
  連結成分に対応する番号とした場合、iからjには有効路が存在するようになっている。
  つまり、連結成分はトポロジカルソートされている。
*/
int scc(const Graph &G, const Graph &rG, int cmp[]) {
  int V = G.size();
  bool used[V];
  std::vector<int> vs;
  std::fill(used, used + V, 0);

  for (int v = 0; v < V; ++v) {
    if (not used[v])
      dfs(G, v, used, &vs);
  }

  std::fill(used, used + V, 0);
  int k = 0;
  for (int i = vs.size() - 1; 0 <= i; --i) {
    if (not used[vs[i]])
      rdfs(rG, vs[i], k++, used, cmp);
  }
  return k;
}

int main() {
  return 0;
}
