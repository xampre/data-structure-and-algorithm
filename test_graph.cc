#include <iostream>
#include <vector>
#include "graph.h"
using namespace std;

template<>
void Graph<>::add_edge(int u, int v) {
  (*this)[u].push_back(v);
}

int main() {
  Graph<> G(5);
  G.add_edge(0, 2);
  cout << G[0][0] << endl;
  return 0;
}

