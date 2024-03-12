#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "link_stack.h"

link_stack link_stack_create()
{
  link_stack s = (link_stack)malloc(sizeof(link_stack_node));
  if (s == NULL)
  {
    printf("link_stack malloc failed\n");
    return NULL;
  }
  return s;
}

void link_stack_clear(link_stack h)
{
  link_stack pre = NULL;
  link_stack next = h->next;
  while (next != NULL)
  {
    if (pre != NULL)
      free(pre);
    pre = next;
    next = next->next;
  }
  if (pre != NULL)
    free(pre);
}

void link_stack_show(link_stack h)
{
  if (h == NULL)
  {
    printf("link_stack is NULL\n");
    return;
  }
  link_stack next = h->next;
  if (next == NULL)
  {
    printf("link_stack is empty\n");
    return;
  }
  printf(">>>>>>>>>>\n");
  printf("link_stack =");
  while (next != NULL)
  {
    printf(" %d ", next->data);
    next = next->next;
  }
  puts("");
  printf(">>>>>>>>>>\n");
}

int link_stack_push(link_stack h, data_t d)
{
  if (h == NULL)
  {
    printf("link_stack is NULL\n");
    return -1;
  }
  link_stack node = (link_stack)malloc(sizeof(link_stack_node));
  if (node == NULL)
  {
    printf("link_stack_push malloc failed\n");
    return -1;
  }
  node->data = d;
  node->next = h->next;
  h->next = node;
  return 0;
}

int link_stack_pop(link_stack h, data_t *d)
{
  int res = link_stack_empty(h);
  if (res != 0)
    return -1;
  link_stack next = h->next;
  *d = next->data;
  h->next = next->next;
  free(next);
  return 0;
}
int link_stack_top(link_stack h, data_t *d)
{
  int res = link_stack_empty(h);
  if (res != 0)
    return -1;
  link_stack next = h->next;
  *d = next->data;
  return 0;
}
int link_stack_free(link_stack h)
{
  int res = link_stack_empty(h);
  if (res == -1)
    return -1;
  if (res == 1)
  {
    free(h);
    return 0;
  }
  link_stack next = h->next;
  while (next != NULL)
  {
    link_stack hit = next;
    next = next->next;
    free(hit);
  }
  return 0;
}
/**
 * 1 是empty
 */
int link_stack_empty(link_stack h)
{
  if (h == NULL)
  {
    printf("link_stack is NULL\n");
    return -1;
  }
  link_stack next = h->next;
  if (next == NULL)
  {
    printf("link_stack is empty\n");
    return 1;
  }
  return 0;
}