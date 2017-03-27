#include <stdio.h>
#include <stdlib.h>
#include "arraylib.h"

void quicksort(int arr[], int size, int (*pivot)(int)) {
  int last = 0;
  if (size <= 1) return;

  swap(arr, &arr[pivot(size)]);
  for (int i = 0; i < size; ++i)
    if (arr[i] < arr[0])
      swap(&arr[i], &arr[++last]);
  swap(arr, &arr[last]);
  quicksort(arr, last, pivot);
  quicksort(arr + last + 1, size - last - 1, pivot);
}

int pivot(int size) {
  return rand() % (size - 1);
}

int main(int argc, char *argv[])
{
  int size = 20;
  int arr[size];

  random_array(arr, size, 2*size);
  print_array(arr, size);
  quicksort(arr, size, pivot);
  print_array(arr, size);

  return 0;
}
