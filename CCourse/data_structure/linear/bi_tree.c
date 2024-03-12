#include <stdlib.h>
#include <stdio.h>
#include "bi_tree.h"
bi_tree bi_tree_create(data_t d)
{
  bi_tree t = (bi_tree)malloc(sizeof(bi_tree_node));
  if (t == NULL)
  {
    printf("bi_tree_create malloc fail\n");
    return NULL;
  }
  t->data = d;
  t->lchild = NULL;
  t->rchild = NULL;
  return t;
}
int bi_tree_create_push_left(bi_tree t, data_t d)
{
  if (t == NULL)
  {
    printf("bi_tree is NULL\n");
    return -1;
  }
  bi_tree node = (bi_tree)malloc(sizeof(bi_tree_node));
  if (node == NULL)
  {
    printf("bi_tree_create_push_left malloc fail\n");
    return -1;
  }
  node->data = d;
  node->lchild = NULL;
  node->rchild = NULL;
  bi_tree parent = t;
  while (parent->lchild != NULL)
  {
    parent = parent->lchild;
  }
  parent->lchild = node;
  return 0;
}
int bi_tree_create_push_right(bi_tree t, data_t d)
{
  if (t == NULL)
  {
    printf("bi_tree is NULL\n");
    return -1;
  }
  bi_tree node = (bi_tree)malloc(sizeof(bi_tree_node));
  if (node == NULL)
  {
    printf("bi_tree_create_push_right malloc fail\n");
    return -1;
  }
  node->data = d;
  node->lchild = NULL;
  node->rchild = NULL;
  bi_tree parent = t;
  while (parent->rchild != NULL)
  {
    parent = parent->rchild;
  }
  parent->rchild = node;
  return 0;
}
void visit(bi_tree t)
{
  printf(" %d ", t->data);
}
// 根 左 右 先序遍历
void bi_tree_iterate_1(bi_tree t)
{
  if (t != NULL)
  {
    visit(t);
    bi_tree_iterate_1(t->lchild);
    bi_tree_iterate_1(t->rchild);
  }
}
//  左 根 右 中序遍历
void bi_tree_iterate_2(bi_tree t)
{
  if (t != NULL)
  {
    bi_tree_iterate_1(t->lchild);
    visit(t);
    bi_tree_iterate_1(t->rchild);
  }
}
//  左 右 根 后序遍历
void bi_tree_iterate_3(bi_tree t)
{
  if (t != NULL)
  {
    bi_tree_iterate_1(t->lchild);
    bi_tree_iterate_1(t->rchild);
    visit(t);
  }
}