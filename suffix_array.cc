#include <iostream>

//#define DEBUG
#define debug(x) std::cout << #x << ": " << (x) << std::endl

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

/*
  Suffix Array
*/
namespace {
  bool compare(int i, int j, int len, int rank[], int k) {
    if (rank[i] != rank[j]) return rank[i] < rank[j];
    int ri = i + k < len ? rank[i + k] : -1;
    int rj = j + k < len ? rank[j + k] : -1;
    return ri < rj;
  }
}

template<class InputIterator>
std::vector<int> suffix_array(InputIterator first, InputIterator last) {
  int len = last - first;
  std::vector<int> sa(len);
  int rank[len];

  std::iota(sa.begin(), sa.end(), 0);
  std::copy(first, last, rank);

  for (int k = 1; k < len; k *= 2) {
    std::sort(sa.begin(), sa.end(),
              [=, &rank](int i, int j) -> bool {
                return compare(i, j, len, rank, k);
              });

    int tmp[len];
    tmp[sa[0]] = 0;
    for (int i = 1; i < len; ++i)
      tmp[sa[i]] = tmp[sa[i - 1]] + compare(sa[i - 1], sa[i], len, rank, k);
    std::copy(tmp, tmp + len, rank);
  }
  return sa;
}

template<class Iterable>
std::vector<int> suffix_array(const Iterable &i) {
  return suffix_array(begin(i), end(i));
}

bool contain(const std::string &str, const std::string &T,
             const std::vector<int> &sa) {
  int lb = 0;
  int ub = str.length() - 1;
  while (1 < ub - lb) {
    int c = (lb + ub) / 2;
    int cmp = str.compare(sa[c], T.length(), T);
    if (cmp < 0) lb = c;
    else if (0 < cmp) ub = c;
    else return true;
  }
  return false;
}

/*
  Longest Common Prefix Array
  要素数は sa.size() - 1。
*/
template<class InputIterator>
std::vector<int> lcp_array(InputIterator first, InputIterator last,
                           const std::vector<int> &sa) {
  int len = last - first;
  int rank[len]; // rank[i] = sa[i] の sa 内でのインデックス
  std::vector<int> res(len - 1);

  for (int i = 0; i < len; ++i)
    rank[sa[i]] = i;

  // 長い接尾辞から順に、その手前に位置するところから作っていく
  int h = 0;
  for (int i = 0; i < len; ++i) {
    if (0 < h) --h;
    if (rank[i] == 0) continue;
    int j = sa[rank[i] - 1];
    while (j + h < len and i + h < len
           and *(first + j + h) == *(first + i + h))
      ++h;
    res[rank[i] - 1] = h;
  }
  return res;
}

template<class Iterable>
std::vector<int> lcp_array(const Iterable &i, const std::vector<int> &sa) {
  return lcp_array(begin(i), end(i), sa);
}

int main() {
  using namespace std;
  string S = "abracadabra";
  auto sa = suffix_array(S);
  vector<int> res_sa = {10, 7, 0, 3, 5, 8, 1, 4, 6, 9, 2};
  debug(res_sa == sa);
  debug(contain(S, S, sa) == 1);
  debug(contain(S, "c", sa) == 1);
  debug(contain(S, "ada", sa) == 1);
  debug(contain(S, "adz", sa) == 0);

  auto lcp = lcp_array(S, sa);
  vector<int> res_lcp = {1, 4, 1, 1, 0, 3, 0, 0, 0, 2};
  debug(res_lcp == lcp);

  return 0;
}
