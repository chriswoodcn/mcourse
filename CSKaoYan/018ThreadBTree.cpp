/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-10 13:35:20
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-11 13:59:53
 * @Description: 线索二叉树/线索二叉树找前驱后继 p47~49
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <vector>
//-----------------------------------------线索二叉树概念-----------------------------------------
// 普通二叉树节点只存储有左子节点和右子节点或父节点,以某种遍历方式（如先序、中序、后序或层次等）进行遍历后,
// 其中的某个节点无法方便的获取前驱和后继,如何记录遍历后的前后关系?  利用n+1的空链域
// 一个节点的左孩子指针和右孩子指针不是指向的左右孩子,而是指向了遍历关系的前驱后继,这种类型的指针称为线索
// 普通二叉树存储结构  二叉链表
#define ElemType int
typedef struct BiNode
{
        ElemType data;
        struct BiNode *lchild, *rchild;
} BiNode, *BiTree;
// 线索二叉树存储结构  线索链表
typedef struct ThreadNode
{
        ElemType data;
        struct ThreadNode *lchild, *rchild;
        int ltag, rtag; // 左右线索标记 tag为1时,才表示指针是线索
} ThreadNode, *ThreadTree;
typedef struct ThreadPNode
{
        ElemType data;
        struct ThreadPNode *lchild, *rchild, *parent;
        int ltag, rtag;
} ThreadPNode, *ThreadPTree;

// 在二叉树的结点上加上线索的二叉树称为线索二叉树
// 3种线索二叉树 先序线索二叉树 中序线索二叉树 后序线索二叉树
//-----------------------------------------二叉树线索化-------------------------------------------
// 对二叉树以某种遍历方式（如先序、中序、后序或层次等）进行遍历，使其变为线索二叉树的过程称为对二叉树进行线索化。
// 中序线索化
// 找中序前驱方法
// void FindInOrderThreadTreePre()
// {

//         ThreadNode *p;                 // p指向目标节点
//         ThreadNode *pre = NULL;        // 指向当前访问节点的前驱
//         ThreadNode *finalPoint = NULL; // 用于记录最终结果
//         void Visit(ThreadNode * q)
//         {
//                 if (q == p) // 当前访问节点刚好是p节点
//                 {
//                         finalPoint = pre; // 找到p的前驱
//                 }
//                 else
//                         pre = q; // pre指向当前访问的节点
//         }
//         void InOrder(ThreadTree t)
//         {
//                 if (t != NULL)
//                 {
//                         InOrder(t->lchild);
//                         Visit(t);
//                         InOrder(t->rchild);
//                 }
//         }
// }
// 中序线索化方法
void InOrder(ThreadTree t, ThreadTree &pre)
{
        if (t != NULL)
        {
                InOrder(t->lchild, pre);
                if (t->lchild == NULL) // 左子树为空,建立前驱线索
                {
                        t->ltag = 1;
                        t->lchild = pre;
                }
                if (pre != NULL && pre->rchild == NULL) // 建立前驱节点的后继线索
                {
                        pre->rtag = 1;
                        pre->rchild = t;
                }
                pre = t; // pre指向当前访问的节点
                InOrder(t->rchild, pre);
        }
}
void CreateInOrderThreadTree(ThreadTree t)
{
        ThreadNode *pre = NULL; // 指向当前访问节点的前驱
        InOrder(t, pre);
        if (pre->rchild == NULL)
                pre->rtag = 1; // 处理遍历的最后一个节点
}
// 先序线索化
void PreOrder(ThreadTree t, ThreadTree &pre)
{
        if (t != NULL)
        {
                if (t->lchild == NULL) // 左子树为空,建立前驱线索
                {
                        t->ltag = 1;
                        t->lchild = pre;
                }
                if (pre != NULL && pre->rchild == NULL) // 建立前驱节点的后继线索
                {
                        pre->rtag = 1;
                        pre->rchild = t;
                }
                pre = t; // pre指向当前访问的节点
                if (t->ltag == 0)
                        PreOrder(t->lchild, pre); // 避免建立了前驱线索后,递归到线索上去,形成循环
                PreOrder(t->rchild, pre);
        }
}
void CreatePreOrderThreadTree(ThreadTree t)
{
        ThreadNode *pre = NULL; // 指向当前访问节点的前驱
        PreOrder(t, pre);
        if (pre->rchild == NULL) // 处理遍历的最后一个节点
                pre->rtag = 1;
}
// 后序线索化
void PostOrder(ThreadTree t, ThreadTree &pre)
{
        if (t != NULL)
        {

                PostOrder(t->lchild, pre);
                PostOrder(t->rchild, pre);
                if (t->lchild == NULL) // 左子树为空,建立前驱线索
                {
                        t->ltag = 1;
                        t->lchild = pre;
                }
                if (pre != NULL && pre->rchild == NULL) // 建立前驱节点的后继线索
                {
                        pre->rtag = 1;
                        pre->rchild = t;
                }
                pre = t; // pre指向当前访问的节点
        }
}
void CreatePostOrderThreadTree(ThreadTree t)
{
        ThreadNode *pre = NULL; // 指向当前访问节点的前驱
        PostOrder(t, pre);
}

void initThreadTree(ThreadTree *T)
{
        *T = (ThreadTree)malloc(sizeof(ThreadNode));
        (*T)->data = 1;
        (*T)->ltag = 0;
        (*T)->rtag = 0;
        ThreadNode *node2 = (ThreadNode *)malloc(sizeof(ThreadNode));
        node2->data = 2;
        node2->ltag = 0;
        node2->rtag = 0;
        (*T)->lchild = node2;
        ThreadNode *node3 = (ThreadNode *)malloc(sizeof(ThreadNode));
        node3->data = 3;
        node3->ltag = 0;
        node3->rtag = 0;
        (*T)->rchild = node3;
        ThreadNode *node4 = (ThreadNode *)malloc(sizeof(ThreadNode));
        node4->data = 4;
        node4->ltag = 0;
        node4->rtag = 0;
        ThreadNode *node5 = (ThreadNode *)malloc(sizeof(ThreadNode));
        node5->data = 5;
        node5->ltag = 0;
        node5->rtag = 0;
        node2->lchild = node4;
        node2->rchild = node5;
        ThreadNode *node6 = (ThreadNode *)malloc(sizeof(ThreadNode));
        node6->data = 6;
        node6->ltag = 0;
        node6->rtag = 0;
        ThreadNode *node7 = (ThreadNode *)malloc(sizeof(ThreadNode));
        node7->data = 7;
        node7->ltag = 0;
        node7->rtag = 0;
        node3->lchild = node6;
        node3->rchild = node7;
        node4->lchild = NULL;
        node4->rchild = NULL;
        node5->lchild = NULL;
        node5->rchild = NULL;
        node6->lchild = NULL;
        node6->rchild = NULL;
        node7->lchild = NULL;
        node7->rchild = NULL;
}
void PrintPreOrder(ThreadTree t)
{
        if (t != NULL)
        {
                printf("elem: %p - %d lchild: %d - %p rchild: %d - %p \n", t, t->data, t->ltag, t->lchild, t->rtag, t->rchild);
                if (t->ltag == 0)
                        PrintPreOrder(t->lchild);
                if (t->rtag == 0)
                        PrintPreOrder(t->rchild);
        }
}
void PrintPreOrderThreadTree(ThreadTree t)
{
        printf("先序遍历ThreadTree\n");
        PrintPreOrder(t);
}
void PrintInOrder(ThreadTree t)
{
        if (t != NULL)
        {

                if (t->ltag == 0)
                        PrintInOrder(t->lchild);
                printf("elem: %p - %d lchild: %d - %p rchild: %d - %p \n", t, t->data, t->ltag, t->lchild, t->rtag, t->rchild);
                if (t->rtag == 0)
                        PrintInOrder(t->rchild);
        }
}
void PrintInOrderThreadTree(ThreadTree t)
{
        printf("中序遍历ThreadTree\n");
        PrintInOrder(t);
}
void PrintPostOrder(ThreadTree t)
{
        if (t != NULL)
        {

                if (t->ltag == 0)
                        PrintPostOrder(t->lchild);
                if (t->rtag == 0)
                        PrintPostOrder(t->rchild);
                printf("elem: %p - %d lchild: %d - %p rchild: %d - %p \n", t, t->data, t->ltag, t->lchild, t->rtag, t->rchild);
        }
}
void PrintPostOrderThreadTree(ThreadTree t)
{
        printf("后序遍历ThreadTree\n");
        PrintPostOrder(t);
}

void TestInOrderThreadTree()
{
        ThreadTree t;
        initThreadTree(&t);
        CreateInOrderThreadTree(t);
        PrintInOrderThreadTree(t);
}
void TestPreOrderThreadTree()
{
        ThreadTree t;
        initThreadTree(&t);
        CreatePreOrderThreadTree(t);
        PrintPreOrderThreadTree(t);
        ThreadNode *node = PreOrder_FindChildTreeLastNode(t->lchild);
        printf("last node %p - %d", node, node->data);
}
void TestPostOrderThreadTree()
{
        ThreadTree t;
        initThreadTree(&t);
        CreatePostOrderThreadTree(t);
        PrintPostOrderThreadTree(t);
}
//-----------------------------------------线索二叉树找前驱后继------------------------------------
// 中序线索二叉树找前驱后继  左 根 右
// 找后继
// p->rtag == 1; next = p->rchild;
// p->rtag == 0; next = ThreadInTree_FindNextNode(p->rchild);
// p->rtag == 0则p必有右孩子 p的后继要么是右孩子(右孩子没有左孩子)要么是右孩子的最左子孙,使用ThreadInTree_FindNextNode方法
ThreadNode *ThreadInTree_FindNextNode(ThreadNode *p)
{
        while (p->ltag == 0)
                p = p->lchild;
        return p;
}
// 找前驱
// p->ltag == 1; pre = p->lchild;
// p->ltag == 0; pre = ThreadInTree_FindPreNode(p->lchild);
// p->ltag == 0则p必有左孩子 p的前驱要么是左孩子(左孩子没有右孩子)要么是左孩子的最右子孙,使用ThreadInTree_FindPreNode方法
ThreadNode *ThreadInTree_FindPreNode(ThreadNode *p)
{
        while (p->rtag == 0)
                p = p->lchild;
        return p;
}
ThreadNode *FirstNode(ThreadTree t)
{
        while (t->ltag == 0)
                t = t->lchild;
        return t;
}
ThreadNode *LastNode(ThreadTree t)
{
        while (t->rtag == 0)
                t = t->rchild;
        return t;
}
ThreadNode *NextNode(ThreadNode *p)
{
        if (p->rtag == 1)
                return p->rchild;
        return FirstNode(p->rchild);
}
ThreadNode *PreNode(ThreadNode *p)
{
        if (p->rtag == 1)
                return p->lchild;
        return LastNode(p->lchild);
}

// 先序线索二叉树找前驱后继 根 左 右
// 找后继
// p->rtag == 1; next = p->rchild;
// p->rtag == 0; next = ThreadPreTree_FindNextNode(p);
// p->rtag == 0则p必有右孩子
// 1.p如果有左孩子 p的后继是左孩子
// 2.p如果没有左孩子 p的后继是右孩子
ThreadNode *ThreadPreTree_FindNextNode(ThreadNode *p)
{
        if (p->ltag == 1 || p->lchild == NULL)
        {
                return p->rchild;
        }
        return p->lchild;
}
// 找前驱
// p->ltag == 1; pre = p->lchild;
// p->ltag == 0; pre = ?
// p->ltag == 0则p必有左孩子 但是无法找到上一层的前驱,这种情况下无法找到前驱节点,除非按照最笨方法遍历
// 三叉链表记录父节点的话
// 1.p如果是左孩子  父节点 p 右孩子    p的前驱节点必定是父节点
// 2.p如果是右孩子  父节点 空 p        p的前驱节点必定是父节点
// 3.p如果是右孩子  父节点 左孩子 p    p的前驱节点为左兄弟树的最后一个先序遍历节点
// 4.p是根节点 没有前驱节点
// 寻找子树的最后一个先序遍历节点
ThreadNode *PreOrder_FindChildTreeLastNode(ThreadNode *p)
{
        int ltag = p->ltag;
        int rtag = p->rtag;
        while (rtag == 0 || ltag == 0)
        {
                if (rtag == 0)
                {
                        p = p->rchild;
                        rtag = p->rtag;
                        ltag = p->ltag;
                        continue;
                }
                if (ltag == 0)
                {
                        p = p->lchild;
                        rtag = p->rtag;
                        ltag = p->ltag;
                        continue;
                }
        }
        return p;
}
// 后序线索二叉树找前驱后继 左 右 根
// 找前驱
// p->ltag == 1; pre = p->lchild;
// p->ltag == 0; pre = ?
// p->ltag == 0则p必有左孩子
// 1.如果没有右孩子,则前驱节点为左孩子;(左 右 根)
// 2.如果有右孩子,则前驱节点为右孩子;(左 右 根)

// 找后继
// p->rtag == 1; next = p->rchild;
// p->rtag == 0则p必有右孩子  但是无法找到上一层的后继
// 三叉链表记录父节点的话
// 1.p如果是右孩子   左孩子 p 父节点        p的后继节点为父节点
// 2.p如果是根结点                         p没有后继节点
// 3.p如果是左孩子   p 空 父节点            p的后继节点为父节点
// 4.p如果是左孩子   p 右孩子 父节点        p的后继节点为右兄弟树的第一个后序遍历节点
ThreadNode *PostOrder_FindChildTreeFirstNode(ThreadNode *p)
{
        int ltag = p->ltag;
        int rtag = p->rtag;
        while (ltag == 0 || rtag == 0)
        {
                if (ltag == 0)
                {
                        p = p->lchild;
                        rtag = p->rtag;
                        ltag = p->ltag;
                        continue;
                }
                if (rtag == 0)
                {
                        p = p->rchild;
                        rtag = p->rtag;
                        ltag = p->ltag;
                        continue;
                }
        }
        return p;
}
int main()
{
        TestPreOrderThreadTree();
        return 0;
}