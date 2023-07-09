/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-07 15:35:19
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-08 19:58:20
 * @Description: 二叉树的遍历和线索二叉树
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
//--------------------------------------------二叉树的遍历----------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#define ElemType int
typedef struct BiTNode
{
        ElemType data;
        struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
void visit(BiTree T)
{
        printf("%d \n", T->data);
}
// 二叉树的遍历
// 先序遍历（根左右）
void PreOrder(BiTree T)
{
        if (T != NULL)
        {
                visit(T);            // 访问根结点
                PreOrder(T->lchild); // 递归遍历左子树
                PreOrder(T->rchild); // 递归遍历右子树
        }
}
// 中序遍历(左根右)
void InOrder(BiTree T)
{
        if (T != NULL)
        {
                InOrder(T->lchild); // 递归遍历左子树
                visit(T);           // 访问根结点
                InOrder(T->rchild); // 递归遍历右子树
        }
}
// 后序遍历(左右根)
void PostOrder(BiTree T)
{
        if (T != NULL)
        {
                PostOrder(T->lchild); // 递归遍历左子树
                PostOrder(T->rchild); // 递归遍历右子树
                visit(T);             // 访问根结点
        }
}
// 求遍历序列
// 1.分支节点逐层展开法 从根节点开始向左右孩子逐层展开
// 根       左          右
// 根 (根   左     右)(根 左)
// 根 (根 (根 右)  右)(根 左)
// 2.画路径方法,每个节点都会路过三次,先序第一次路过访问,中序第二次路过访问,后序第三次路过访问

// 求树的深度
int TreeDeep(BiTree T)
{
        if (T == NULL)
                return 0;
        else
        {
                int ldeep = TreeDeep(T->lchild);
                int rdeep = TreeDeep(T->rchild);
                return (ldeep > rdeep) ? (ldeep + 1) : (rdeep + 1);
        }
}

// 二叉树的层次遍历
// 算法思想： 初始化一个辅助队列,根节点入队,若队列非空，则队头结点出队，访问该结点，依次将其左、右孩子插入队尾（如果有的话）重复以上操作直至队列为空
typedef struct LinkNode
{
        BiTNode data;
        struct LinkNode *next;
} LinkNode;
typedef struct
{
        LinkNode *front;
        LinkNode *rear;
        int length;
} LinkQueue;

void InitQueue(LinkQueue &Q)
{
        Q.front = Q.rear = NULL;
        Q.length = 0;
}
void EnQueue(LinkQueue &Q, BiTNode *node)
{
        LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
        p->data = (*node);
        p->next = NULL;
        if (Q.length == 0)
        {
                Q.front = Q.rear = p;
        }
        else
        {
                Q.rear->next = p;
                Q.rear = p;
        }
        Q.length++;
}
bool DeQueue(LinkQueue &q, BiTNode &e)
{
        if (q.front == NULL)
                return false;
        LinkNode *p = q.front;
        e = p->data;
        q.front = p->next;
        if (q.rear == p)
                q.rear = q.front;
        free(p);
        q.length--;
        return true;
}
void initTestFlatBiTree(BiTree &T)
{
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = 1;
        BiTNode *node2 = (BiTNode *)malloc(sizeof(BiTNode));
        node2->data = 2;
        T->lchild = node2;
        BiTNode *node3 = (BiTNode *)malloc(sizeof(BiTNode));
        node3->data = 3;
        T->rchild = node3;
        BiTNode *node4 = (BiTNode *)malloc(sizeof(BiTNode));
        node4->data = 4;
        BiTNode *node5 = (BiTNode *)malloc(sizeof(BiTNode));
        node5->data = 5;
        node2->lchild = node4;
        node2->rchild = node5;
        BiTNode *node6 = (BiTNode *)malloc(sizeof(BiTNode));
        node6->data = 6;
        BiTNode *node7 = (BiTNode *)malloc(sizeof(BiTNode));
        node7->data = 7;
        node3->lchild = node6;
        node3->rchild = node7;
        node4->lchild=NULL;
        node4->rchild=NULL;
        node5->lchild=NULL;
        node5->rchild=NULL;
        node6->lchild=NULL;
        node6->rchild=NULL;
        node7->lchild=NULL;
        node7->rchild=NULL;
}
void TestFlatBiTree()
{
        LinkQueue q;
        InitQueue(q);
        BiTree t;
        initTestFlatBiTree(t);
        printf("%d ", t->data);
        printf("%p ", t->lchild);
        printf("%p \n", t->rchild);
        EnQueue(q, t);
        while (q.length != 0)
        {
                BiTNode node;
                DeQueue(q, node);
                printf("%d \n", node.data);
                if (node.lchild != NULL)
                        EnQueue(q, node.lchild);
                if (node.rchild != NULL)
                        EnQueue(q, node.rchild);
        }
}
int main()
{
        TestFlatBiTree();
        return 0;
}
