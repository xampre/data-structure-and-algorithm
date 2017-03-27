/*
  Floyd-Warshall algorithm
*/

#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>

#define debug(x) cout << #x << ": " << (x) << endl
#define INF (INT_MAX/3)

struct edge { int to, cost; };

typedef std::vector<std::vector<edge> > Graph;

template<class Matrix>
void init_dp(const Graph &G, Matrix dp) {
  size_t V = G.size();
  for (size_t i = 0; i < V; ++i) {
    for (size_t j = 0; j < V; ++j)
      (*dp)[i][j] = INF;
    (*dp)[i][i] = 0;

    for (size_t j = 0; j < G[i].size(); ++j) {
      int to = G[i][j].to;
      (*dp)[i][to] = G[i][j].cost;
    }
  }
}

template<class Matrix>
void floyd_warshall(const Graph &G, Matrix dp) {
  int V = G.size();
  init_dp(G, dp);

  for (int k = 0; k < V; ++k) {
    for (int i = 0; i < V; ++i) {
      for (int j = 0; j < V; ++j) {
        (*dp)[i][j] = std::min((*dp)[i][j], (*dp)[i][k] + (*dp)[k][j]);
      }
    }
  }
}

int main() {
  const int N = 4;
  Graph G(N);
  int dp[N][N];
  int res[N][N] = {
    {0, -1, -2, 0},
    {4, 0, 2, 4},
    {5, 1, 0, 2},
    {3, -1, 1, 0}
  };

  G[0].push_back({2, -2});
  G[1].push_back({0, 4});
  G[1].push_back({2, 3});
  G[2].push_back({3, 2});
  G[3].push_back({1, -1});

  floyd_warshall(G, &dp);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (dp[i][j] != res[i][j]) {
        std::cout << "False" << std::endl;
        return 0;
      }
    }
  }

  std::cout << "True" << std::endl;
  return 0;
}

