#include <iostream>
#include <vector>
#include "uft.h"

#define debug(x) std::cout << #x << ": " << (x) << std::endl

int main() {
  UFT u = UFT(10);
  debug(u.same(1, 2) == false);
  debug(u.find(2) == 2);
  u.unite(1, 2);
  debug(u.same(1, 2) == true);
  debug(u.find(1) == 1);
  debug(u.find(2) == 1);
  return 0;
}
