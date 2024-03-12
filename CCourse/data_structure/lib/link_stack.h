#ifndef LINK_STACK_H
#define LINK_STACK_H

typedef int data_t;
typedef struct node
{
  data_t data;
  struct node *next;
} link_stack_node, *link_stack;

link_stack link_stack_create();
void link_stack_clear(link_stack h);
void link_stack_show(link_stack h);
int link_stack_push(link_stack h, data_t d);
int link_stack_pop(link_stack h, data_t *d);
int link_stack_top(link_stack h, data_t *d);
int link_stack_free(link_stack h);
int link_stack_empty(link_stack h);

#endif // LINK_STACK_H