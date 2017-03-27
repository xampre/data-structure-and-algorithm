#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include "matrix.h"

#define debug(x) cout << #x << ": " << (x) << endl

using namespace std;

typedef vector<double> VD;
typedef Matrix<double> MD;

double EPS = numeric_limits<double>::epsilon();

/*
  gauss_jordan

  Ax = b を解く。 Aは正方行列
  解がないか、一意でない場合は長さ0の配列を返す
*/
VD gauss_jordan(const MD &A, const VD &b) {
  int n = A.row();
  MD B = A.col_joined(b);

  for (int i = 0; i < n; ++i) {
    // 注目している係数の絶対値が大きい式をi行目に持ってくる
    int pivot = i;
    for (int j = i; j < n; ++j) {
      if (abs(B[pivot][i]) < abs(B[j][i]))
        pivot = j;
    }
    B.swap_rows(i, pivot);

    // 解がないか、一意でない。
    if (abs(B[i][i]) < EPS) return VD();

    // 注目している係数を1にする
    for (int j = i + 1; j <= n; ++j) B[i][j] /= B[i][i];
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        // j行i列目を0にする行列の操作
        for (int k = i + 1; k <= n; ++k)
          B[j][k] -= B[j][i] * B[i][k];
      }
    }
  }

  VD x(n);
  for (int i = 0; i < n; ++i)
    x[i] = B[i][n];
  return x;
}

int main() {
  double a[] = {1,-2,3, 4,-5,6, 7,-8,10};
  MD A(3, a);
  VD b = {6, 12, 21};
  VD ans = {1.0, 2.0, 3.0};
  VD res = gauss_jordan(A, b);
  for (int i = 0; i < 3; ++i) {
    double diff = abs(res[i] - ans[i]);
    debug((diff < 15*EPS) == true);
  }
  return 0;
}
