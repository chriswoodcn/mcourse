/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-29 13:46:35
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-29 15:32:48
 * @Description: 队列的链式实现
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
// -------------------------------------------队列的链式实现------------------------------------------------------
// 队列是只允许在一端插入,在另一端删除的线性表 入队 出队
// 重要术语 队头 队尾 空队列 先进先出 first in first out FIFO
// InitQueue(&Q) 初始化队列
// DestroyQueue(&Q) 销毁队列
// EnQueue(&Q,e) 入队
// DeQueue(&Q,e) 出队
// GetHead(Q,&e) 读队头元素
#include <iostream>
#include <stdlib.h>

#define ELemType int
#define MaxSize 10
typedef struct LinkNode
{
        ELemType data;
        struct LinkNode *next;
} LinkNode;
typedef struct
{
        LinkNode *front;
        LinkNode *rear;
        int length;
} LinkQueue;
bool InitLinkQueue(LinkQueue &q)
{
        q.front = q.rear = (LinkNode *)malloc(sizeof(LinkNode));
        q.front->next = NULL;
        q.length = 0;
        return true;
}
bool InitNoHeadLinkQueue(LinkQueue &q)
{
        q.front = q.rear = NULL;
        q.length = 0;
        return true;
}
void PrintLinkQueue(LinkQueue &q)
{
        LinkNode *p = q.front->next;
        std::cout << "LinkQueue: " << std::endl;
        if (p == NULL)
                std::cout << "Empty" << std::endl;
        while (p != NULL)
        {
                std::cout << p->data << " ";
                p = p->next;
        }
        std::cout << " \n"
                  << std::endl;
}
void PrintNoHeadLinkQueue(LinkQueue &q)
{
        LinkNode *p = q.front;
        std::cout << "NoHeadLinkQueue: " << std::endl;
        if (p == NULL)
                std::cout << "Empty" << std::endl;
        while (p != NULL)
        {
                std::cout << p->data << " ";
                p = p->next;
        }
        std::cout << " \n"
                  << std::endl;
}
bool DestroyLinkQueue(LinkQueue &q)
{
        LinkNode *p = q.front->next;
        while (p != NULL)
        {
                q.front->next = p->next; // 队顶更换为下一个
                free(p);                 // 释放原先的队顶指针
                p = q.front->next;
        }
        q.rear = q.front;
        q.length = 0;
        return true;
}
bool DestroyNoHeadLinkQueue(LinkQueue &q)
{
        LinkNode *p = q.front;
        while (p != NULL)
        {
                q.front = p->next; // 队顶更换为下一个
                free(p);           // 释放原先的队顶指针
                p = q.front;
        }
        q.rear = NULL;
        q.length = 0;
        return true;
}
bool EnQueue(LinkQueue &q, ELemType e)
{
        LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
        p->data = e;
        p->next = NULL;
        q.rear->next = p;
        q.rear = p;
        q.length++;
        return true;
}
bool EnNoHeadQueue(LinkQueue &q, ELemType e)
{
        LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
        p->data = e;
        p->next = NULL;
        if (q.rear == NULL) // 队尾为NULL时
        {
                q.front = q.rear = p;
        }
        else
        {
                q.rear->next = p;
                q.rear = p;
        }
        q.length++;
        return true;
}
bool DeQueue(LinkQueue &q, ELemType &e)
{
        if (q.front->next == NULL)
                return false;
        LinkNode *p = q.front->next;
        e = p->data;
        q.front->next = p->next;
        if (q.rear == p)
                q.rear = q.front;
        free(p);
        q.length--;
        return true;
}
bool DeNoHeadQueue(LinkQueue &q, ELemType &e)
{
        if (q.front == NULL)
                return false;
        LinkNode *p = q.front;
        e = p->data;
        q.front = p->next;
        if (q.rear == p)
                q.front = q.rear = NULL;
        free(p);
        q.length--;
        return true;
}
void TestQueue()
{
        LinkQueue q;
        InitLinkQueue(q);
        ELemType e;
        EnQueue(q, 1);
        EnQueue(q, 2);
        EnQueue(q, 3);
        EnQueue(q, 4);
        EnQueue(q, 5);
        PrintLinkQueue(q);
        printf("length: %d\n", q.length);
        DeQueue(q, e);
        DeQueue(q, e);
        PrintLinkQueue(q);
        printf("length: %d\n", q.length);
        LinkQueue nhq;
        InitNoHeadLinkQueue(nhq);
        EnNoHeadQueue(nhq, 10);
        EnNoHeadQueue(nhq, 20);
        EnNoHeadQueue(nhq, 30);
        EnNoHeadQueue(nhq, 40);
        EnNoHeadQueue(nhq, 50);
        EnNoHeadQueue(nhq, 60);
        PrintNoHeadLinkQueue(nhq);
        printf("length: %d\n", nhq.length);
        DeNoHeadQueue(nhq, e);
        PrintNoHeadLinkQueue(nhq);
        printf("length: %d\n", nhq.length);
}
int main()
{
        TestQueue();
        return 0;
}
