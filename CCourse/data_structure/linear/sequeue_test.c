#include <stdio.h>
#include "sequeue.h"

int main()
{
  sequeue *s = queue_create();
  queue_show(s);
  enqueue(s, 100);
  queue_show(s);
  enqueue(s, 200);
  queue_show(s);
  enqueue(s, 300);
  queue_show(s);
  enqueue(s, 400);
  queue_show(s);
  enqueue(s, 500);
  queue_show(s);
  enqueue(s, 600);
  queue_show(s);
  for (int i = 0; i < 3; i++)
  {
    int v;
    int res = dequeue(s, &v);
    if (res == 0)
    {
      printf("dequeue value = %d \n", v);
    }
  }
  queue_show(s);
  enqueue(s, 500);
  queue_show(s);
  enqueue(s, 600);
  queue_show(s);
  return 0;
}