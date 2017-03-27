#include <stdio.h>
#include "arraylib.h"

void shellsort(int nums[], int size, int interval) {
  for ( ; interval > 0; interval /=  2)
    for (int i = 0; i < size; ++i)
      for (int j = i; (interval <= j) && (nums[j] < nums[j - interval]); j -= interval)
        swap(&nums[j], &nums[j - interval]);
}

int main(int argc, char *argv[]) {
  int interval = 4;
  int size = 20;
  int a[size];

  random_array(a, size, 2*size);
  print_array(a, size);
  shellsort(a, size, interval);
  print_array(a, size);
  return 0;
}
