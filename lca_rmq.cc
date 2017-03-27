/*
  Lowest Common Ancester

  Using RMQ

  Note: Copy constructor not implemented
 */

#include <iostream>
#include <vector>

#define debug(x) std::cout << #x << ": " << (x) << std::endl;

// Begin code
#include <utility>
#include <climits>
#include "rmq.h"

typedef RMQ<std::pair<int, int> > _RMQ;
const int INF = INT_MAX / 3;

class LCAFinder {
  int *vs; // DFSでの訪問順 (i.e DFSが0 -> 1 -> 0 -> 3 ... と訪問したなら vs = {0, 1, 0, 3, ...})
  int *id; // 木の頂点vがvsで最初に出現する場所のインデックス
  _RMQ *rmq;

protected:

  template<class Graph>
  void dfs(const Graph &G, int v, int p, int d, int &k,
           std::pair<int, int> depth[]) {
    id[v] = k;
    vs[k] = v;
    depth[k] = std::make_pair(d, k);
    ++k;
    for (size_t i = 0; i < G[v].size(); ++i) {
      if (G[v][i] != p) {
        dfs(G, G[v][i], v, d + 1, k, depth);
        vs[k] = v;
        depth[k] = std::make_pair(d, k);
        ++k;
      }
    }
  }

public:

  template<class Graph>
  LCAFinder(const Graph &G, int root) {
    const int V = G.size();
    vs = new int [2*V - 1];
    id = new int [V];
    std::pair<int, int> depth[2*V - 1]; // 木の頂点vを探索している時のDFSの再帰の深さ

    int k = 0;
    dfs(G, root, -1, 0, k, depth);
    rmq = new _RMQ(depth, depth + 2*V - 1, std::make_pair(INF, INF));
  }

  ~LCAFinder() {
    delete [] vs;
    delete [] id;
    delete rmq;
  }

  int lca(int u, int v) {
    return vs[rmq->min(std::min(id[u], id[v]),
                       std::max(id[u], id[v]) + 1).second];
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
