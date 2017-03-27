#pragma once

#include <vector>

typedef std::vector<std::vector<int> > Graph;

std::size_t tpsort_dfs(const Graph &, int []);
std::size_t tpsort_Kahn(Graph *, int []);
