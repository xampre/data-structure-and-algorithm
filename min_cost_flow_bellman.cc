/*
  Minimum Cost Problem

  グラフに負の閉路がない場合に使用できる
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define INF (INT_MAX/3)
#define debug(x) cout << #x << ": " << (x) << endl
//#define DEBUG

struct edge { int to, cap, cost, rev; };
typedef vector<vector<edge> > Graph;

void add_edge(Graph *G, int from, int to, int cap, int cost) {
  int rev1 = (*G)[to].size();
  int rev2 = (*G)[from].size();
  (*G)[from].push_back({to, cap, cost, rev1});
  (*G)[to].push_back({from, 0, -cost, rev2});
}

void shortest_path_bellman(const Graph &G, const int s,
                            int dist[], int prev_v[], int prev_e[]) {
  int V = G.size();
  bool update = true;
  fill(dist, dist + V, INF);
  dist[s] = 0;
  while (update) {
    update = false;
    for (int v = 0; v < V; ++v) {
      if (dist[v] == INF) continue;
      for (size_t i = 0; i < G[v].size(); ++i) {
        const edge &e = G[v][i];
        int new_cost = dist[v] + e.cost;
        if (0 < e.cap and new_cost < dist[e.to]) {
          dist[e.to] = new_cost;
          prev_v[e.to] = v;
          prev_e[e.to] = i;
          update = true;
        }
      }
    }
  }
}

int min_cost_flow(Graph G, int s, int t, int f) {
  int V = G.size();
  int res = 0;
  int dist[V];
  int prev_v[V];
  int prev_e[V];

  while (0 < f) {
    shortest_path_bellman(G, s, dist, prev_v, prev_e);

    if (dist[t] == INF) return -1; // これ以上流せない

    int flow = f;
    for (int v = t; v != s; v = prev_v[v]) {
      flow = min(flow, G[prev_v[v]][prev_e[v]].cap);
    }

    f -= flow;
    res += flow * dist[t];
    for (int v = t; v != s ; v = prev_v[v]) {
      edge &e = G[prev_v[v]][prev_e[v]];
      e.cap -= flow;
      G[v][e.rev].cap += flow;
    }
  }
  return res;
}

int main() {
  Graph G(5);
  add_edge(&G, 0, 1, 10, 2);
  add_edge(&G, 0, 2, 2, 4);
  add_edge(&G, 1, 2, 6, 6);
  add_edge(&G, 1, 3, 6, 2);
  add_edge(&G, 2, 4, 5, 2);
  add_edge(&G, 3, 2, 3, -3);
  add_edge(&G, 3, 4, 8, 6);
  debug(min_cost_flow(G, 0, 4, 1) == 3);
  debug(min_cost_flow(G, 0, 4, 3) == 9);
  debug(min_cost_flow(G, 0, 4, 9) == 68);
  return 0;
}
