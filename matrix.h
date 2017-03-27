#pragma once

#include <algorithm>
#include <cassert>

template<typename T>
class Matrix {
  int n_row, n_col;
  T **mat;

  void set_members(const int n_row, const int n_col, const T v) {
    this->n_row = n_row;
    this->n_col = n_col;
    this->mat = new T * [n_row];
    for (int i = 0; i < n_row; ++i) {
      this->mat[i] = new T [n_col];
      std::fill(this->mat[i], this->mat[i] + n_col, v);
    }
  }

  void set_members(const int n_row, const int n_col, const T a[]) {
    this->n_row = n_row;
    this->n_col = n_col;
    this->mat = new T * [n_row];
    for (int i = 0; i < n_row; ++i) {
      this->mat[i] = new T [n_col];
      std::copy(a + i*n_col, a + (i + 1)*n_col, this->mat[i]);
    }
  }

  void set_members(const Matrix<T> &A) {
    this->n_row = A.n_row;
    this->n_col = A.n_col;
    this->mat = new T * [n_row];
    for (int i = 0; i < n_row; ++i) {
      this->mat[i] = new T [n_col];
      std::copy(A.mat[i], A.mat[i] + n_col, this->mat[i]);
    }
  }

  void del_mat() {
    for (int i = 0; i < n_row; ++i)
      delete [] mat[i];
    delete [] mat;
  }

public:

  Matrix(const int n_row, const int n_col) { set_members(n_row, n_col, T()); }
  Matrix(const int n): Matrix(n, n) {}
  Matrix(const int n_row, const int n_col, const T a[]) { set_members(n_row, n_col, a); }
  Matrix(const int n, const T a[]): Matrix(n, n, a) {}
  Matrix(const Matrix<T> &A) { set_members(A); }
  ~Matrix() { del_mat(); }

  Matrix<T> &operator=(const Matrix<T> &other) {
    if (this != &other) {
      del_mat();
      set_members(other);
    }
    return *this;
  }

  T *operator[](const int i) const { return mat[i]; }

  bool operator ==(const Matrix<T> &other) const {
    if (n_row != other.n_row) return false;
    if (n_col != other.n_col) return false;
    for (int i = 0; i < n_row; ++i) {
      for (int j = 0; j < n_col; ++j) {
        if (mat[i][j] != other.mat[i][j])
          return false;
      }
    }
    return true;
  }

  Matrix<T> operator*(const Matrix<T> &other) const {
    return Matrix<T>::mul(*this, other);
  }

  int row() const { return n_row; }
  int col() const { return n_col; }

  T at(const int i, const int j) const {
    return this->mat[i][j];
  }

  template<class C>
  Matrix<T> col_joined(const C col) const {
    Matrix<T> B(n_row, n_col + 1);
    for (int i = 0; i < n_row; ++i) {
      std::copy(mat[i], mat[i] + n_col, B[i]);
      B[i][n_col] = col[i];
    }
    return B;
  }

  template<class C>
  Matrix<T> row_joined(const C row) const {
    Matrix<T> B(n_row + 1, n_col);
    for (int i = 0; i < n_row; ++i)
      std::copy(mat[i], mat[i] + n_col, B[i]);
    std::copy(row, row + n_col, B[n_row]);
    return B;
  }

  void swap_rows(int n1, int n2) {
    assert(n1 < n_row);
    assert(n2 < n_row);
    T temp[n_col];
    std::copy(mat[n1], mat[n1] + n_col, temp);
    std::copy(mat[n2], mat[n2] + n_col, mat[n1]);
    std::copy(temp, temp + n_col, mat[n2]);
  }

  void swap_cols(int n1, int n2) {
    assert(n1 < n_col);
    assert(n2 < n_col);
    for (int i = 0; i < n_row; ++i)
      std::swap(mat[i][n1], mat[i][n2]);
  }

  static Matrix<T> mul(const Matrix<T> &A, const Matrix<T> &B) {
    assert(A.n_col == B.n_row);
    int M = A.n_row,
      N = B.n_col,
      K = A.n_col;
    Matrix<T> C(M, N);

    for (int i = 0; i < M; ++i) {
      for (int k = 0; k < K; ++k) {
        for (int j = 0; j < N; ++j) {
          C[i][j] = C[i][j] + A.mat[i][k] * B.mat[k][j];
        }
      }
    }
    return C;
  }

  Matrix<T> mul(const Matrix<T> &other) {
    return Matrix<T>::mul(*this, other);
  }

  static Matrix<T> pow(const Matrix<T> &A, const int n) {
    assert(A.n_row == A.n_col);
    int M = A.n_row;
    int bit = n;
    Matrix<T> B(M, M);
    Matrix<T> C(A);

    for (int i = 0; i < M; ++i)
      B[i][i] = 1;

    while (0 < bit) {
      if (bit & 1) B.mul(C);
      C.mul(C);
      bit >>= 1;
    }
    return B;
  }

  Matrix<T> pow(const int n) {
    return Matrix<T>::pow(*this, n);
  }

  static Matrix<T> transpose(const Matrix<T> A) {
    Matrix<T> C(A.n_col, A.n_row);
    for (int i = 0; i < A.n_row; ++i) {
      for (int j = 0; j < A.n_col; ++j) {
        C[j][i] = A.mat[i][j];
      }
    }
    return C;
  }

  Matrix<T> transpose() {
    return Matrix<T>::transpose(*this);
  }

  static Matrix<T> eye(const int n) {
    Matrix<T> A(n);
    for (int i = 0; i < n; ++i)
      A[i][i] = 1;
    return A;
  }

};
