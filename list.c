#include <stdio.h>
#include <stdlib.h>

#define car(list) ((list)->val)
#define cdr(list) ((list)->next)

typedef struct _list {
  int val;
  struct _list *next;
} List;

List *cons(int val, List *list) {
  List *l = malloc(sizeof(List));
  if (l == NULL) return NULL;
  l->val = val;
  l->next = list;
  return l;
}

void print_list(List *list) {
  List *l = list;
  printf("[");
  for ( ; cdr(l) != NULL; l = cdr(l))
    printf("%d, ", car(l));
  printf("%d]\n", car(l));
}

int main(int argc, char *argv[]) {
  List *list = cons(0, cons(1, cons(2, cons(3, NULL))));
  print_list(list);
  return 0;
}
