#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MULTIPLIER 2

typedef struct _list {
  char *key;
  char *value;
  struct _list *next;
} List;

typedef struct {
  int size;
  List **lists;
} H_Table;

List *new_list(char *key, char *value, List *next) {
  List *l = malloc(sizeof(List));
  if (l == NULL) return NULL;

  l->key = (char *)strdup(key);
  l->value = (char *)strdup(value);
  if (l->key == NULL || l->value == NULL) {
    free(l);
    return NULL;
  }

  l->next = next;
  return l;
}

void del_list(List *l) {
  free(l->key);
  free(l->value);
  free(l);
  l = NULL;
}

H_Table *new_table(int size) {
  H_Table *htable = malloc(sizeof(H_Table));
  List **lists = malloc(sizeof(List) * size);
  if (htable == NULL || lists == NULL)
    return NULL;
  for (int i = 0; i < size; lists[i++] = NULL)
    ;
  htable->size = size;
  htable->lists = lists;
  return htable;
}

void del_table(H_Table *htable) {
  for (int i = 0; i < htable->size; ++i) {
    List *l = htable->lists[i];
    while (l != NULL) {
      List *next = l->next;
      del_list(l);
      l = next;
    }
  }
  free(htable->lists);
  free(htable);
}

unsigned int hash(char *str) {
  unsigned int h = 0;
  unsigned char *p = (unsigned char *)str;
  for ( ; *p != '\0'; ++p)
    h = MULTIPLIER * h + *p;
  return h;
}

/*
 */
List *lookup(H_Table *htable, char *key, bool create, char *value) {
  int i = hash(key) % htable->size;

  for (List *l = htable->lists[i]; l != NULL; l = l->next) {
    if (strcmp(l->key, key) == 0) { // key is found
      if (create) {
        free(l->value);
        l->value = (char *)strdup(value);
      }
      return l;
    }
  }

  // key is not found
  // or htable[i] is NULL
  if (create) {
    List *add = new_list(key, value, htable->lists[i]);
    if (add == NULL) return NULL;
    htable->lists[i] = add;
    return add;
  }

  return NULL;
}

bool set_value(H_Table *htable, char *key, char *value) {
  return lookup(htable, key, true, value) ? true : false;
}

char *get_value(H_Table *htable, char *key) {
  List *list = lookup(htable, key, false, NULL);
  return list ? list->value : NULL;
}

void print_table(H_Table *htable) {
  for (int i = 0; i < htable->size; ++i) {
    List *l = htable->lists[i];
    if (l == NULL) continue;
    while (l != NULL) {
      printf("{%s: %s} -> ", l->key, l->value);
      l = l->next;
    }
    printf("NULL\n");
  }
}

int main(int argc, char *argv[])
{
  int size = 7;
  H_Table *htable = new_table(size);
  char *val = NULL;
  char *key_value[][2] = {
    {"1", "a"}, {"2", "b"}, {"3", "c"},
    {"4", "d"}, {"5", "e"}, {"6", "f"},
    {"7", "g"}, {"8", "h"}, {"9", "i"},
    {"1", "aa"}
  };

  for (int i = 0; i < sizeof(key_value)/sizeof(key_value[0]); ++i)
    set_value(htable, key_value[i][0], key_value[i][1]);

  print_table(htable);
  val = get_value(htable, "10");
  val = val ? val : get_value(htable, "1");
  if (val != NULL)
    printf("%s\n", val);
  del_table(htable);
  return 0;
}
