/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-28 07:52:53
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-29 13:18:06
 * @Description: 数据结构-栈
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
// -------------------------------------------栈的链式存储------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#pragma region 链栈
#define ElemType int
// 头插法建立单链表 对应进栈
// 对头结点的删除操作 对应出栈
typedef struct LinkNode
{
        ElemType data;
        struct LinkNode *next;
} LinkNode, *LinkStack;
bool InitLinkStack(LinkStack &stack)
{
        stack = (LinkStack)malloc(sizeof(struct LinkNode));
        if (stack == NULL)
                return false;
        stack->next = NULL;
        return true;
}
bool PushLinkStack(LinkStack &stack, ElemType e)
{
        LinkStack p = (LinkStack)malloc(sizeof(struct LinkNode));
        if (p == NULL)
                return false;
        p->data = e;
        p->next = stack->next;
        stack->next = p;
        return true;
}
bool PopLinkStack(LinkStack &stack, ElemType &e)
{
        if (stack->next == NULL)
                return false;
        e = stack->next->data;
        LinkNode *p = stack->next;
        stack->next = stack->next->next;
        free(p);
        return true;
}
void PrintLinkStack(LinkStack &stack)
{
        LinkStack p = stack->next;
        printf("ListStack: ");
        if (p == NULL)
                printf("Empty");
        while (p != NULL)
        {
                printf("%d ", p->data);
                p = p->next;
        }
        printf("\n");
}
bool EmptyLinkStack(LinkStack &stack)
{
        return stack->next == NULL;
}
LinkNode *TopLinkStack(LinkStack &stack)
{
        return stack->next;
}
void TestLinkStack()
{
        LinkStack stack;
        InitLinkStack(stack);
        PushLinkStack(stack, 1);
        PushLinkStack(stack, 2);
        PushLinkStack(stack, 3);
        PrintLinkStack(stack);
        ElemType e;
        PopLinkStack(stack, e);
        printf("PopElem: %d \n", e);
        PrintLinkStack(stack);
        LinkNode* top = TopLinkStack(stack);
        printf("TopElem: %d \n", top->data);
}
#pragma endregin 链栈
int main()
{
        TestLinkStack();
        return 0;
}
