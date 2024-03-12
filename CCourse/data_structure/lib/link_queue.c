#include <stdlib.h>
#include <stdio.h>
#include "link_queue.h"

link_queue *queue_create()
{
  link_list l = (link_list)malloc(sizeof(list_node));
  if (l == NULL)
  {
    printf("queue_create malloc link_list failed\n");
    return NULL;
  }
  l->next = NULL;
  link_queue *q = (link_queue *)malloc(sizeof(link_queue));
  if (q == NULL)
  {
    printf("queue_create malloc link_queue failed\n");
    return NULL;
  }
  q->front = q->rear = l;
  return q;
}

void queue_clear(link_queue *q)
{
  int check = queue_empty(q);
  if (check != 0)
    return;
  while (q->rear != q->front)
  {
    int r;
    dequeue(q, &r);
  }
}

void queue_show(link_queue *q)
{
  int check = queue_empty(q);
  if (check != 0)
    return;
  printf(">>>>>>>>>>\n");
  printf("front = %p\n", q->front);
  printf("rear = %p\n", q->rear);
  link_list h = q->front->next;
  printf(" %d ", h->data);
  while (h != q->rear)
  {
    h = h->next;
    printf(" %d ", h->data);
  }
  puts("");
  printf(">>>>>>>>>>\n");
}

int enqueue(link_queue *q, data_t d)
{
  int check = queue_empty(q);
  if (check == -1)
    return -1;
  link_list insert = (link_list)malloc(sizeof(list_node));
  if (insert == NULL)
  {
    printf("enqueue malloc failed\n");
    return -1;
  }
  // insert->data = d;
  // insert->next = q->front->next;
  // q->front->next = insert;
  // if (check == 1)
  // {
  //   q->rear = insert;
  // }
  // 上面是先进后出了，下面是先进先出
  insert->data = d;
  insert->next = NULL;
  q->rear->next = insert;
  q->rear = insert;
  return 0;
}

int dequeue(link_queue *q, data_t *v)
{
  int check = queue_empty(q);
  if (check != 0)
    return -1;
  link_list pop = q->front->next;
  *v = pop->data;
  q->front->next = pop->next;
  if (pop->next == NULL)
  {
    q->rear = q->front;
  }
  free(pop);
  return 0;
}

int queue_empty(link_queue *q)
{
  if (q == NULL)
  {
    printf("link_queue is NULL\n");
    return -1;
  }
  if (q->front == q->rear)
  {
    printf("link_queue is empty\n");
    return 1;
  }
  return 0;
}

int queue_free(link_queue *q)
{
  int check = queue_empty(q);
  if (check == -1)
    return -1;
  if (check == 0)
  {
    while (q->front != q->rear)
    {
      int r;
      dequeue(q, &r);
    }
  }
  free(q);
  return 0;
}
