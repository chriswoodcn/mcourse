#ifndef BI_TREE_H
#define BI_TREE_H

typedef int data_t;
typedef struct node
{
  data_t data;
  struct node *lchild, *rchild;
} bi_tree_node, *bi_tree;

bi_tree bi_tree_create(data_t d);
int bi_tree_create_push_left(bi_tree t, data_t d);
int bi_tree_create_push_right(bi_tree t, data_t d);
void bi_tree_iterate_1(bi_tree t);
void bi_tree_iterate_2(bi_tree t);
void bi_tree_iterate_3(bi_tree t);

#endif // BI_TREE_H