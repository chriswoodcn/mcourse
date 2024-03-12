#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link_hash.h"
link_hash_node_p createMap(int value)
{
  link_hash_node_p p = (link_hash_node_p)malloc(sizeof(link_hash_node));
  if (p == NULL)
  {
    return NULL;
  }
  p->key = value;
  p->value = value;
  p->next = NULL;
  return p;
}
void link_hash_operate()
{
  link_hash *h = link_hash_create(18, 13);
  link_hash_insert(h, createMap(23));
  link_hash_show(h);
  link_hash_insert(h, createMap(34));
  link_hash_insert(h, createMap(14));
  link_hash_insert(h, createMap(38));
  link_hash_insert(h, createMap(46));
  link_hash_insert(h, createMap(16));
  link_hash_insert(h, createMap(68));
  link_hash_insert(h, createMap(15));
  link_hash_insert(h, createMap(7));
  link_hash_insert(h, createMap(31));
  link_hash_insert(h, createMap(26));
  link_hash_show(h);
  int res = link_hash_search(h, 68);
  printf("link_hash_search 68 res = %d\n", res);
  res = link_hash_search(h, 99);
  printf("link_hash_search 99 res = %d\n", res);
  res = link_hash_search(h, 7);
  printf("link_hash_search 7 res = %d\n", res);
}
int main()
{
  link_hash_node arr[10];
  for (int i = 0; i < 10; i++)
  {
    link_hash_node_p p = &arr[i];
    if (p == NULL)
    {
      printf("&arr[%d] is NULL \n", i);
    }
    else
    {
      printf("&arr[%d] address = %p \n", i, p);
    }
  }

  link_hash_node_p arr2 = (link_hash_node_p)malloc(sizeof(link_hash_node) * 10);
  for (int i = 0; i < 10; i++)
  {
    link_hash_node_p p = &arr2[i];
    if (p == NULL)
    {
      printf("&arr2[%d] is NULL \n", i);
    }
    else
    {
      printf("&arr2[%d] address = %p \n", i, p);
    }
  }

  link_hash_operate();
  return 0;
}