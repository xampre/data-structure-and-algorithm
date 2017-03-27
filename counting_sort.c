#include <stdio.h>
#include "arraylib.h"

/*
  nums: 数字の配列。
  size: numsのデータの個数。
  range: 対象の各データは 0 以上 range 未満の値をとる。
*/
void counting_sort(int nums[], int size, int range)
{
  int i, j;
  int offset = 0;
  int buckets[range];

  for (i = 0; i < range; ++i)
    buckets[i] = 0;

  for (i = 0; i < size; ++i)
    buckets[nums[i]]++;

  for (i = 0; i < range; ++i)
    for (j = 0; j < buckets[i]; ++j)
      nums[offset++] = i;
}

int main()
{
  int a[] = {7, 5, 4, 3, 2, 1};

  counting_sort(a, 6, 8);
  print_array(a, 6);
  return 0;
}
