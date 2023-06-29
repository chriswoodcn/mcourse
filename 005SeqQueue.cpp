/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-29 13:46:35
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-29 14:27:43
 * @Description: 队列的顺序实现
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
// -------------------------------------------队列的顺序实现------------------------------------------------------
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
typedef struct
{
        ELemType data[MaxSize]; // 静态数组存放队列元素
        int front, rear;        // 队头游标和队尾游标
} SqQueue;
bool InitSqQueue(SqQueue &q)
{
        q.front = q.rear = 0; // 队头游标和队尾游标都指向0
        return true;
}
bool EmptyQueue(SqQueue &q)
{
        return q.front == q.rear;
}
bool DestroySqQueue(SqQueue &q)
{
        q.front = q.rear = 0;
        return true;
}
bool EnQueue(SqQueue &q, ELemType e)
{
        if ((q.rear + 1) % MaxSize == q.front) // 队列已满的条件
                return false;
        q.data[q.rear] = e;
        q.rear = (q.rear + 1) % MaxSize; // 队尾指针+1 取模 10/10 回到第一个指针
        return true;
}
bool DeQueue(SqQueue &q, ELemType &e)
{
        if (EmptyQueue(q))
                return false;
        e = q.data[q.front];
        q.front = (q.front + 1) % MaxSize; // 队头指针+1
        return true;
}
bool GetHead(SqQueue &q, ELemType &e)
{
        if (q.front == q.rear)
                return false;
        e = q.data[q.front];
        return true;
}
int ELemCountQueue(SqQueue &q)
{
        return (q.rear - q.front + MaxSize) % MaxSize;
}
void PrintQueue(SqQueue &q)
{
        for (int i = q.front; i < q.rear; i++)
                std::cout << q.data[i] << " ";
        std::cout << std::endl;
}
void TestQueue()
{
        SqQueue q;
        InitSqQueue(q);
        ELemType e;
        EnQueue(q, 1);
        EnQueue(q, 2);
        EnQueue(q, 3);
        EnQueue(q, 4);
        EnQueue(q, 5);
        EnQueue(q, 6);
        PrintQueue(q);
        std::cout << "队列元素个数 " << ELemCountQueue(q) << std::endl;
        DeQueue(q, e);
        std::cout << e << std::endl;
        DeQueue(q, e);
        std::cout << e << std::endl;
        DeQueue(q, e);
        std::cout << e << std::endl;
        PrintQueue(q);
        std::cout << "队列元素个数 " << ELemCountQueue(q) << std::endl;
}
int main()
{
        TestQueue();
        return 0;
}
