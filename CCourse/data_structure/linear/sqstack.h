#ifndef SQSTACK_H
#define SQSTACK_H
#endif // SQSTACK_H

typedef int data_t;
typedef struct
{
  data_t *data; /*指针指向栈的存储空间*/
  int maxlen;   /*当前栈的最大元素个数*/
  int top;      /*当前栈顶位置 数组下标*/
} sqstack;

sqstack *stack_create(int len);

void stack_clear(sqstack *s);

void stack_show(sqstack *s);

int stack_push(sqstack *s, data_t v);

int stack_pop(sqstack *s, data_t *d);

int stack_top(sqstack *s, data_t *d);

int stack_free(sqstack *s);

int stack_empty(sqstack *s);