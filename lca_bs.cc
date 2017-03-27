/*
  Lowest Common Ancestor

  Using Binary Search

  Complexity: O(log(V))
    Initialization: O(V log(V))
    where V: number of vertices of the tree

  Note: Copy constructor not implemented
*/

#include <iostream>
#include <vector>

//#define DEBUG
#define debug(x) std::cout << #x << ": " << (x) << std::endl

// Begin code
#include <cmath>
#include <algorithm>

class LCAFinder {
  int logV;
  int *depth;
  int **parent;

protected:

  // parent[0]とdepthを初期化
  template<class Graph>
  void dfs(const Graph &G, int v, int p, int d) {
    parent[0][v] = p;
    depth[v] = d;
    for (size_t i = 0; i < G[v].size(); ++i)
      if (G[v][i] != p)
        dfs(G, G[v][i], v, d + 1);
  }

public:

  template<class Graph>
  LCAFinder(const Graph &G, int root): logV(floor(log2(G.size()))) {
    const int V = G.size();
    depth = new int [V];
    parent = new int* [logV];
    for (int i = 0; i < logV; ++i)
      parent[i] = new int [V];

    dfs(G, root, -1, 0);

    // parentを初期化。
    for (int k = 0; k + 1 < logV; ++k) {
      for (int v = 0; v < V; ++v) {
        if (parent[k][v] < 0)
          parent[k + 1][v] = -1;
        else
          parent[k + 1][v] = parent[k][parent[k][v]];
      }
    }
  }

  ~LCAFinder() {
    delete [] depth;
    for (int i = 0; i < logV; ++i)
      delete [] parent[i];
    delete [] parent;
  }

  int lca(int u, int v) {
    if (depth[v] < depth[u]) std::swap(u, v);

    // uとvの深さが同じになるまで親を辿る
    for (int k = 0; k < logV; ++k) {
      if ((depth[v] - depth[u]) >> k & 1)
        v = parent[k][v];
    }

    if (u == v) return u;

    for (int k = logV - 1; 0 <= k; --k) {
      if (parent[k][u] != parent[k][v]) {
        u = parent[k][u];
        v = parent[k][v];
      }
    }
    return parent[0][u];
  }

};

// End code

int main() {
  typedef std::vector<std::vector<int> > Graph;
  const int N = 8;
  Graph G(N);
  G[0].push_back(1);
  G[0].push_back(2);
  G[1].push_back(3);
  G[1].push_back(4);
  G[2].push_back(5);
  G[4].push_back(6);
  G[4].push_back(7);

  LCAFinder f(G, 0);
  debug(f.lca(4, 5) == 0);
  debug(f.lca(6, 7) == 4);
  debug(f.lca(5, 6) == 0);
  debug(f.lca(3, 7) == 1);
  return 0;
}
