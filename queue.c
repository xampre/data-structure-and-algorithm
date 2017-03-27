#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct _node {
  int value;
  struct _node *newer;
} Node;

typedef struct _queue {
  Node *newest;
  Node *oldest;
} Queue;

Queue *new_queue() {
  Queue *queue = malloc(sizeof(Queue));
  if (queue == NULL) return NULL;
  queue->newest = NULL;
  queue->oldest = NULL;
  return queue;
}

void del_queue(Queue *queue) {
  Node *newer = queue->oldest;
  while (newer != NULL) {
    newer = newer->newer;
    free(queue->oldest);
    queue->oldest = newer;
  }
}

bool is_empty(Queue *queue) {
  return queue->oldest == NULL ? true : false;
}

bool enqueue(int val, Queue *queue) {
  Node *add = malloc(sizeof(Queue));
  if (add == NULL)
    return false;

  add->value = val;
  add->newer = NULL;
  if (is_empty(queue))
    queue->oldest = add;
  else
    queue->newest->newer = add;
  queue->newest = add;
  return true;
}

int dequeue(Queue *queue) {
  int value;
  Node *res;

  res = queue->oldest;
  queue->oldest = res->newer;
  value = res->value;
  free(res);
  return value;
}

int main(int argc, char *argv[])
{
  const int N = 100000;
  Queue *queue = new_queue();

  for (int i = 0; i < N; ++i)
    enqueue(i, queue);

  for (int i = 0; !is_empty(queue) && i < 10; ++i) {
    int val = dequeue(queue);
    printf("%d\n", val);
  }

  del_queue(queue);
  return 0;
}
