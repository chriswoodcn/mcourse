#include <stdio.h>
#include "link_stack.h"

int main()
{
  link_stack s = link_stack_create();
  link_stack_show(s);
  link_stack_push(s, 1);
  link_stack_push(s, 2);
  link_stack_push(s, 3);
  link_stack_show(s);
  return 0;
}