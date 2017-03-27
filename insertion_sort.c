#include <stdio.h>
#include "arraylib.h"

void insertion_sort(int nums[], int size) {
  for (int i = 1; i < size; ++i)
    for (int j = i; (0 < j) && (nums[j] < nums[j - 1]); --j)
      swap(&nums[j - 1], &nums[j]);
}

int main() {
  int a[] = {1, 3, 7, 9, 2, 3, 4, 1};
  int size = sizeof(a)/sizeof(a[0]);

  insertion_sort(a, size);
  print_array(a, size);
  return 0;
}
