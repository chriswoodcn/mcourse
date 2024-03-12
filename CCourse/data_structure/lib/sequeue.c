#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sequeue.h"

sequeue *queue_create()
{
  sequeue *s = (sequeue *)malloc(sizeof(sequeue));
  if (s == NULL)
  {
    printf("queue_create malloc failed\n");
    return NULL;
  }
  memset(s->data, 0, sizeof(s->data));
  s->front = 0;
  s->rear = 0;
  return s;
}

void queue_clear(sequeue *s)
{
  if (s == NULL)
  {
    printf("sequeue is NULL\n");
    return;
  }
  s->rear = s->front = 0;
}

void queue_show(sequeue *s)
{
  int res = queue_empty(s);
  if (res != 0)
    return;
  printf(">>>>>>>>>>\n");
  printf("front = %d\n", s->front);
  printf("rear = %d\n", s->rear);
  int max = s->rear > s->front ? s->rear : s->rear + N;
  for (int i = s->front; i < max; i++)
  {
    printf(" %d ", s->data[i % N]);
  }
  puts("");
  printf(">>>>>>>>>>\n");
}

int enqueue(sequeue *s, data_t d)
{
  int res = queue_full(s);
  if (res != 0)
    return -1;
  s->data[s->rear] = d;
  s->rear = (s->rear + 1) % N;
  return 0;
}

int dequeue(sequeue *s, data_t *v)
{
  int res = queue_empty(s);
  if (res != 0)
    return -1;
  *v = s->data[s->front];
  s->front = (s->front + 1) % N;
  return 0;
}

int queue_empty(sequeue *s)
{
  if (s == NULL)
  {
    printf("sequeue is NULL\n");
    return -1;
  }
  if (s->rear == s->front)
  {
    printf("sequeue is empty\n");
    return 1;
  }
  return 0;
}

int queue_full(sequeue *s)
{
  if (s == NULL)
  {
    printf("sequeue is NULL\n");
    return -1;
  }
  if ((s->rear + 1) % N == s->front)
  {
    printf("sequeue is full\n");
    return 1;
  }
  return 0;
}

int queue_free(sequeue *s)
{
  if (s == NULL)
  {
    printf("sequeue is NULL\n");
    return -1;
  }
  free(s);
  return 0;
}
