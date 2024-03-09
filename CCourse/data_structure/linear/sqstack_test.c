#include <stdio.h>
#include "sqstack.h"

int main()
{
  sqstack *s = stack_create(10);
  int res = stack_empty(s);
  printf("stack is empty = %d\n", res);
  stack_push(s, 100);
  stack_push(s, 200);
  stack_push(s, 300);
  stack_push(s, 400);
  data_t pop;
  stack_pop(s, &pop);
  printf("stack pop = %d\n", pop);
  data_t top;
  stack_top(s, &top);
  printf("now stack top is %d\n", top);
  stack_show(s);
  stack_free(s);
  return 0;
}