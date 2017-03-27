#include <iostream>
#include <string>

#define debug(x) std::cout << #x << ": " << (x) << std::endl
//#define DEBUG

bool contain_rolling_hash(std::string a, std::string b, unsigned long long B = 100000007) {
  int al = a.length();
  int bl = b.length();
  if (bl < al) return false;

  unsigned long long ah = 0;
  unsigned long long bh = 0;
  for (int i = 0; i < al; ++i) {
    ah = ah*B + a[i];
    bh = bh*B + b[i];
  }

  unsigned long long t = 1;
  for (int i = 0; i < al; ++i)
    t *= B;

  for (int i = 0; i + al < bl; ++i) {
    if (ah == bh) return true;
    bh = bh*B + b[i + al] - b[i]*t;
  }

  return ah == bh ? true : false;
}

// aの末尾とbの先頭を何文字まで重ねることが出来るか
int overlap_rolling_hash(std::string a, std::string b, unsigned long long B = 100000007) {
  int al = a.length(), bl = b.length();
  int res = 0;
  unsigned long long ah = 0, bh = 0, t = 1;
  for (int i = 1; i <= std::min(al, bl) ; ++i) {
    ah = a[al - i] * t + ah;
    bh = bh*B + b[i - 1];
    if (ah == bh) res = i;
    t *= B;
  }
  return res;
}

int main() {
  std::string a1 = "aa";
  std::string a2 = "zz";
  std::string a3 = "jifejioabca";
  std::string str = "abcaadkejifoejdnie";
  debug(contain_rolling_hash(a1, str) == 1);
  debug(contain_rolling_hash(a2, str) == 0);
  debug(overlap_rolling_hash(a3, str) == 4);
  return 0;
}
