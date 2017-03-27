#include <stdio.h>
#include <stdlib.h>
#include "arraylib.h"

#define LEFT(n) (2*(n))
#define RIGHT(n) (LEFT(n) + 1)

/*
 * shift_down
 *
 * 1. 左右の子の大きい方が nums[n] より大きければ入れ替える。
 * 2. 左右の子の双方が nums[n] 以下になるか、
 *    子のインデックスが bottom より大きくなるまで 1 を繰り返す。
 */
void shift_down(int nums[], int n, int bottom) {
  int max_child;
  int val = nums[n];
  int left = LEFT(n);
  int right = RIGHT(n);

  while (left <= bottom) {
    max_child = (left == bottom || nums[left] > nums[right]) ? left : right;

    if (val < nums[max_child]) {
      swap(&nums[n], &nums[max_child]);
      n = max_child;
      left = LEFT(n);
      right = RIGHT(n);
    } else {
      break;
    }
  }
}

void build_heap(int nums[], int size) {
  int last = size - 1;
  // 下から上
  for (int i = (size / 2) - 1; 0 <= i; --i)
    shift_down(nums, i, last);
}

void heap_sort(int nums[], int size) {
  build_heap(nums, size);

  // sort
  for (int i = size - 1; 0 < i; --i) {
    swap(nums, nums + i);
    shift_down(nums, 0, i - 1);
  }
}

int main() {
  int size = 20;
  int nums[size];
  random_array(nums, size, 2*size);
  print_array(nums, size);
  heap_sort(nums, size);
  print_array(nums, size);
  return 0;
}
