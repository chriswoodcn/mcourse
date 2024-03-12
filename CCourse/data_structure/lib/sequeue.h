#ifndef SEQUEUE_H
#define SEQUEUE_H

#define N 5
typedef int data_t;
typedef struct
{
  data_t data[N];
  int front;
  int rear;
} sequeue;

sequeue *queue_create();
void queue_clear(sequeue *s);
void queue_show(sequeue *s);
int enqueue(sequeue *s, data_t d);
int dequeue(sequeue *s, data_t *v);
int queue_empty(sequeue *s);
int queue_full(sequeue *s);
int queue_free(sequeue *s);

#endif // SEQUEUE_H