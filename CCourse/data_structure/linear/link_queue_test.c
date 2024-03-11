#include <stdio.h>
#include "link_queue.h"

int main()
{
  link_queue *q = queue_create();
  queue_empty(q);
  enqueue(q, 1);
  enqueue(q, 2);
  enqueue(q, 3);
  enqueue(q, 4);
  enqueue(q, 5);
  queue_show(q);
  int r;
  dequeue(q, &r);
  printf("dequeue r = %d \n", r);
  dequeue(q, &r);
  printf("dequeue r = %d \n", r);
  dequeue(q, &r);
  printf("dequeue r = %d \n", r);
  dequeue(q, &r);
  printf("dequeue r = %d \n", r);
  dequeue(q, &r);
  printf("dequeue r = %d \n", r);
  queue_show(q);
  dequeue(q, &r);
  queue_show(q);
  queue_free(q);
  return 0;
}