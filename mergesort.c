#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arraylib.h"

void merge(int ary1[], int size1, int ary2[], int size2, int to[]) {
  int i = 0;
  int i1 = 0;
  int i2 = 0;

  for ( ; i < size1 + size2; ++i) {
    if (i1 < size1 && (i2 >= size2 || ary1[i1] < ary2[i2])) {
      to[i] = ary1[i1];
      i1 += 1;
    } else {
      to[i] = ary2[i2];
      i2 += 1;
    }
  }
}

void split_merge(int ary[], int begin, int end, int work[]) {
  if (end - begin < 2) return;

  int mid = begin + (end - begin)/2;
  split_merge(ary, begin, mid, work);
  split_merge(ary, mid, end, work);
  merge((ary + begin), mid - begin, (ary + mid), end - mid, work);
  copy_array(work, (ary + begin), end - begin);
}

int mergesort(int ary[], int size) {
  int work[size];
  // initialize work
  for (int i = 0; i < size; work[i++] = 0)
    ;

  split_merge(ary, 0, size, work);
  return 0;
}

int main(int argc, char *argv[]) {
  int a[] = {0,2,4,5,33,4,2,1,24,5,6,7,4,44,23,6,7};
  int as = sizeof(a)/sizeof(a[0]);

  mergesort(a, as);
  print_array(a, as);
}
