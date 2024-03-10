#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sqstack.h"

sqstack *stack_create(int len)
{
  sqstack *s = (sqstack *)malloc(sizeof(sqstack));
  s->data = (data_t *)malloc(len * sizeof(data_t));
  s->maxlen = len;
  s->top = -1;
  return s;
}

void stack_clear(sqstack *s)
{
  s->top = -1;
}

void stack_show(sqstack *s)
{
  printf(">>>>>>>>>>\n");
  printf("sqstack maxlen = %d \n", s->maxlen);
  printf("sqstack top = %d \n", s->top);
  printf("sqstack data = ");
  if (s->top >= 0)
  {
    data_t *data = s->data;
    for (int i = 0; i < s->top + 1; i++)
    {
      printf(" %d ", data[i]);
    }
  }
  puts("");
  printf(">>>>>>>>>>\n");
}

int stack_push(sqstack *s, data_t v)
{
  if (s == NULL)
  {
    printf("s is NULL\n");
    return -1;
  }
  if (s->top == s->maxlen)
  {
    printf("s is full\n");
    return -1;
  }
  s->data[++(s->top)] = v;
  return -1;
}

int stack_pop(sqstack *s, data_t *data)
{
  if (s == NULL)
  {
    printf("s is NULL\n");
    return -1;
  }
  if (s->top == -1)
  {
    printf("s is empty\n");
    return -1;
  }
  *data = s->data[(s->top)--];
  return 0;
}

int stack_top(sqstack *s, data_t *data)
{
  if (s == NULL)
  {
    printf("s is NULL\n");
    return -1;
  }
  if (s->top == -1)
  {
    printf("s is empty\n");
    return -1;
  }
  *data = s->data[s->top];
  return 0;
}

int stack_free(sqstack *s)
{
  if (s == NULL)
  {
    printf("s is NULL\n");
    return -1;
  }
  if (s->data != NULL)
    free(s->data);
  free(s);
  return 0;
}

int stack_empty(sqstack *s)
{
  if (s == NULL)
  {
    printf("s is NULL\n");
    return -1;
  }
  return s->top == -1 ? 0 : -1;
}