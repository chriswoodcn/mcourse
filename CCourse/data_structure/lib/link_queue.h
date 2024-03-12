#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

typedef int data_t;
typedef struct node
{
  data_t data;
  struct node *next;
} list_node, *link_list;

typedef struct
{
  link_list front, rear;
} link_queue;

link_queue *queue_create();
void queue_clear(link_queue *q);
void queue_show(link_queue *q);
int enqueue(link_queue *q, data_t d);
int dequeue(link_queue *q, data_t *v);
int queue_empty(link_queue *q);
int queue_free(link_queue *q);

#endif // LINK_QUEUE_H