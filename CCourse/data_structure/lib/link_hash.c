#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "link_hash.h"

link_hash *link_hash_create(int len, int salt)
{
  link_hash_node_p *p = (link_hash_node_p *)malloc(sizeof(link_hash_node_p) * len);
  if (p == NULL)
  {
    printf("link_hash_create malloc link_hash_node fail\n");
    return NULL;
  }
  link_hash *h = (link_hash *)malloc(sizeof(link_hash));
  if (h == NULL)
  {
    printf("link_hash_create malloc link_hash fail\n");
    return NULL;
  }
  memset(p, 0, sizeof(link_hash_node_p) * len);
  h->data = p;
  h->len = len;
  h->salt = salt;
  return h;
}
void link_hash_clear(link_hash *h)
{
}
void link_hash_show(link_hash *h)
{
  if (h == NULL)
  {
    printf("link_hash is NULL\n");
    return;
  }
  printf(">>>>>>>>>>\n");
  for (int i = 0; i < h->len; i++)
  {
    printf("index = %d;", i);
    link_hash_node_p p = h->data[i];
    while (p != NULL)
    {
      printf(" key=%d,value=%d ", p->key, p->value);
      p = p->next;
    }
    puts("");
  }
}
int link_hash_insert(link_hash *h, link_hash_node_p p)
{
  if (h == NULL)
  {
    printf("link_hash is NULL\n");
    return -1;
  }
  if (p == NULL)
  {
    printf("link_hash_node_p is NULL\n");
    return -1;
  }
  int index = p->key % h->salt;
  link_hash_node_p v = h->data[index];
  if (v == NULL)
  {
    h->data[index] = p;
  }
  else
  {
    while (v->next != NULL)
    {
      v = v->next;
    }
    v->next = p;
  }
  return 0;
}
int link_hash_search(link_hash *h, data_t key)
{
  if (h == NULL)
  {
    printf("link_hash is NULL\n");
    return -1;
  }
  int index = key % h->salt;
  link_hash_node_p v = h->data[index];
  while (v != NULL)
  {
    if (v->key == key)
      return index;
    v = v->next;
  }
  return -1;
}