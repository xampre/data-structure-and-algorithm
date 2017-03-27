#pragma once

#include <vector>

#define VVE std::vector<std::vector<Edge, Allocator>, VAllocator>

template <class Edge = int,
          class Allocator = std::allocator<Edge>,
          class VAllocator = std::allocator<std::vector<Edge> > >
class Graph : private VVE {
public:
  using VVE::vector;
  using VVE::at;
  using VVE::size;
  using VVE::resize;
  using VVE::operator[];
  void add_edge(int, int, Edge);
  void add_edge(int, int);
  void remove_edge(int, int);
};
