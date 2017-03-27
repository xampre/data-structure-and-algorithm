#include <stdlib.h>
#include <unistd.h>
#include "arraylib.h"

void selection_sort(int nums[], int size) {
  int i_min;
  for (int i = 0; i < size - 1; ++i) {
    i_min = i;
    for (int j = i + 1; j < size; ++j)
      if (nums[j] < nums[i_min])
        i_min = j;
    swap(nums + i, nums + i_min);
  }
}

int main() {
  int a2[] = {2, 1};
  int size = 20;
  int a[size];

  random_array(a, size, 2*size);
  selection_sort(a2, 2);
  print_array(a2, 2);
  print_array(a, size);
  selection_sort(a, size);
  print_array(a, size);
  return 0;
}
