#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define LEFT(n) (2*(n))
#define RIGHT(n) (2*(n) + 1)

typedef struct {
  int *array;
  int size;
  int items;
} B_Heap;

B_Heap *new_heap(int size) {
  int *array = malloc(sizeof(int) * size);
  B_Heap *heap = malloc(sizeof(B_Heap));

  for (int i = 0; i < size; array[i++] = 0)
    ;
  heap->array = array;
  heap->size = size;
  heap->items = 0;
  return heap;
}

void del_heap(B_Heap *heap) {
  free(heap->array);
  free(heap);
}

void insert(B_Heap *heap, int val) {
  int i = ++heap->items;
  for ( ; (1 < i) && (heap->array[i / 2] < val); i /= 2)
    heap->array[i] = heap->array[i / 2];
  heap->array[i] = val;
}

bool has_child(B_Heap *heap, int n) {
  return LEFT(n) <= heap->items;
}

void print_heap(B_Heap *heap) {
  int i, l, r;
  for (i = 1; has_child(heap, i); ++i) {
    printf("parent [%d]: %d\n", i, heap->array[i]);

    l = LEFT(i);
    printf("\tchild L [%d]: %d\n", l, heap->array[l]);

    r = RIGHT(i);
    if (r < heap->size)
      printf("\tchild R [%d]: %d\n", r, heap->array[r]);
  }
}

int main(void) {
  int size = 21;
  B_Heap *heap = new_heap(size);

  srand(getpid());
  for (int i = 1; i < size; ++i) {
    int val = rand() % 40;
    insert(heap, val);
    printf("Insert [%d]: %d\n", i, val);
  }

  puts("----------------------");
  print_heap(heap);
  del_heap(heap);
  return 0;
}
