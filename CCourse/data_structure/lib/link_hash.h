#ifndef LINK_HASH_H
#define LINK_HASH_H

typedef int data_t;
typedef struct node
{
  data_t key;
  data_t value;
  struct node *next;
} link_hash_node, *link_hash_node_p;
typedef struct
{
  link_hash_node_p *data;
  int len;
  int salt;
} link_hash;

link_hash *link_hash_create(int len, int salt);
void link_hash_clear(link_hash *h);
void link_hash_show(link_hash *h);
int link_hash_insert(link_hash *h, link_hash_node_p p);
int link_hash_search(link_hash *h, data_t key);

#endif