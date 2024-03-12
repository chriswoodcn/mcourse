#include <stdio.h>
#include "bi_tree.h"

int main()
{
  bi_tree root = bi_tree_create(1);
  bi_tree_create_push_left(root, 2);
  bi_tree_create_push_right(root, 3);
  bi_tree_create_push_left(root->lchild, 4);
  bi_tree_create_push_right(root->lchild, 5);
  bi_tree_create_push_left(root->rchild, 6);
  bi_tree_create_push_right(root->rchild, 7);
  // 先序遍历
  bi_tree_iterate_1(root);
  puts("");
  bi_tree_iterate_2(root);
  puts("");
  bi_tree_iterate_3(root);
  puts("");
  return 0;
}