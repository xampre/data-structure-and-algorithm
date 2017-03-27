#pragma once

/*
  Union Find Tree
*/
class UFT {
  int *par;
  int *rank;

public:
  UFT(const int);
  ~UFT();
  int find(int);
  void unite(int, int);
  bool same(int, int);
};
