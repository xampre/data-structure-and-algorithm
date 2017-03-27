#include <iostream>
#include <vector>
#include "matrix.h"

#define debug(x) cout << #x << ":	" << (x) << endl;
using namespace std;

typedef Matrix<int> MI;

void test_mul() {
  int an[] = {1,0,0, 0,1,0, 0,0,1};
  int res[] = {1,1,2,2, 0,1,0,1, 1,1,1,2};
  int al[] = {1,1,2,2, 0,1,0,1, 1,1,1,2};
  MI N(3, an);
  MI R(3, 4, res);
  MI L(3, 4, al);
  debug(N * N == N);
  debug(N * L == R);
  debug(N.mul(L) == R);
}

void test_transpose() {
  int al[] = {1,1,2,2, 0,1,0,1, 1,1,1,2};
  int alt[] = {1,0,1, 1,1,1, 2,0,1, 2,1,2};
  MI L(3, 4, al);
  MI LT(4, 3, alt);
  debug(L.transpose() == LT);
}

void test_joined() {
  int an[] = {1,0,0, 0,1,0, 0,0,1};
  int j[] = {1, 2, 3};
  int jc[] = {1,0,0,1, 0,1,0,2, 0,0,1,3};
  int jr[] = {1,0,0, 0,1,0, 0,0,1, 1,2,3};
  MI N(3, an);
  MI JC(3, 4, jc);
  MI JR(4, 3, jr);

  debug(N.col_joined(j) == JC);
  debug(N.row_joined(j) == JR);
}

void test_swap() {
  int a[] = {1,2,3, 1,2,3};
  int res[] = {2,1,3, 2,1,3};
  MI A(2, 3, a);
  MI RES(2, 3, res);
  A.swap_cols(0, 1);
  cout << "swap:	" << (A == RES) << endl;
}

int main() {
  int an[] = {1,0,0, 0,1,0, 0,0,1};
  MI I = MI::eye(3);
  MI N(3, an);

  cout << "eye():	" << (I == N) << endl;
  debug(N[1][1] == 1);
  debug(N.pow(3) == N);
  test_mul();
  test_transpose();
  test_joined();
  test_swap();
  return 0;
}
