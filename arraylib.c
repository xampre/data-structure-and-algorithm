#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arraylib.h"

void swap(int *x, int *y) {
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

void print_array(int ary[], int size) {
  if (size < 1) {
    printf("{}\n");
    return;
  }

  int last = size - 1;
  printf("{");
  for (int i = 0; i < last; ++i)
    printf("%d,", ary[i]);
  printf("%d}\n", ary[last]);
}

void copy_array(int from[], int to[], int len) {
  for (int i = 0; i < len; ++i) {
    to[i] = from[i];
  }
}

void random_array(int arr[], int size, int range) {
  srand((unsigned int)time(NULL) * range);
  for (int i = 0; i < size; ++i)
    arr[i] = rand() % range;
}
