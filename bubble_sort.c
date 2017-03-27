#include <stdio.h>
#include <stdlib.h>
#include "arraylib.h"

void bubble_sort(int nums[], int size) {
  for (int i = 0; i < (size - 1) ; ++i)
    for (int j = 1; j < (size - i); ++j)
      if (nums[j] < nums[j - 1])
        swap(&nums[j - 1], &nums[j]);
}

int main() {
  int a0[] = {};
  int a1[] = {1};
  int a[] = {6,5,3,3,1,7,2,4};
  int as = sizeof(a)/sizeof(a[0]);
  bubble_sort(a0, 0);
  bubble_sort(a1, 1);
  bubble_sort(a, as);
  print_array(a0, 0);
  print_array(a1, 1);
  print_array(a, as);
  return 0;
}
