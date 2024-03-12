#include <stdio.h>
#include <stdlib.h>
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
int main()
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
  return 0;
}