/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-06 09:57:26
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-07 15:31:36
 * @Description: 二叉树定义/性质/存储结构 p41~p43
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
//---------------------------------------二叉树定义-----------------------------------------
// 二叉树是n(n>=0)个结点的有限集，它或者是空集（n=0），或者由一个根结点及两颗互不相交的分别称作这个根的左子树和右子树的二叉树组成。
// 特点：
// 每个结点最多有俩孩子（二叉树中不存在度大于2的结点）。
// 二叉树可以是空集合，根可以有空的左子树和空的右子树。
// 二叉树有左右之分，次序不能颠倒。

//----------------------------------------二叉树性质---------------------------------------
// 二叉树性质常见考点
// 1.非空二叉树上度为0/1/2的节点个数各为 n0,n1,n2 则n0=n2+1
// 节点总数 = 总度数 + 1 = n1 + 2n2 + 1 = n0 + n1 + n2 所以 n0 = n2 + 1
// 2.在二叉树的第i层上至多有2^（i-1）个结点（i>1）。
// 3.高度为k的二叉树至多有2^k-1个结点（k>=1）。
// 等比数列 m^h - 1 / m - 1 , m = 2
// 完全二叉树常见考点
// 1.具有n个结点的完全二叉树的高度h为 ⌈log2(n+1)⌉ 或⌊log2n⌋+1。
// 2^(h-1) <= n <= 2^h - 1
// 2.完全二叉树n个节点可以推出度为0/1/2的节点个数各为 n0,n1,n2
// 完全二叉树最多只有0或者1个度为1的节点  n1=0或1  又n0=n2+1  n0+n2为奇数
// 当n为2k时(偶数)  n1=1 n0=k n2=k-1
// 当n为2k-1时(奇数) n1=0 n0=k n2=k-1

// 几种特殊的二叉树
//  1.满二叉树
//  颗深度为k且有2^k-1个结点的二叉树称为满二叉树。每一层上的结点数都达到最大。叶子全部在最低层
//  2.完全二叉树
//  深度为k的具有n个结点的二叉树，当且仅当其每一个结点都与深度为k的满二叉树中编号为1~n的结点一 一对应时，称之为完全二叉树
//  3.二叉排序树
//  左子树上所有节点的关键字<根节点
//  右子树上所有节点的关键字>根节点
//  左右子树各是一棵二叉排序树
//  4.平衡二叉树
//  树上任一节点的左子树和右子树的深度只差不超过1
//--------------------------------------二叉树的存储结构------------------------------------
// 顺序存储
#include <stdbool.h>
#define MaxSize 100
#define ElemType int
struct TreeNode
{
        ElemType value; // 结点中的数据元素
        bool isEmpty;   // 结点是否为空
}
// 顺序存储常考基本操作,按照位序进行存储情况下即数组下标0不存数据
// i的左孩子  2i<n ? 2i : NULL
// i的右孩子  2i+1<n ? 2i+1 : NULL
// i的父节点  ⌊i/2⌋
// i所在层次  ⌊log2i⌋+1
// i是否叶子节点 i > n/2
// ***二叉树的顺序存储中,一定要把二叉树的节点编号同完全二叉树对应起来

// 链式存储
// 二叉树的结点
struct ElemType
{
        int value;
};
typedef struct BiTnode
{
        ElemType data;                   // 数据域
        struct BiTNode *lchild, *rchild; // 左、右孩子指针
} BiTNode, *BiTree;
// 三叉链表
typedef struct BiTnode2
{
        ElemType data;                   // 数据域
        struct BiTNode *lchild, *rchild; // 左、右孩子指针
        struct BiTNode *parent;          // 父节点指针
} BiTNode2, *BiTree2;

void TestLinkStructure()
{
        // 定义一棵空树
        BiTree root = NULL;
        root = (BiTree)malloc(sizeof(BiTNode));
        root->data = {1};
        root->lchild = NULL;
        root->rchild = NULL;
        // 插入新结点
        BiTNode *p = (BiTree)malloc(sizeof(BiTNode));
        p->data = {2};
        p->lchild = NULL;
        p->rchild = NULL;
        root->lchild = p; // 作为根节点的左孩子

        // 找到指定结点p的左/右孩子
        // 找到指定结点p的父节点；只能从根结点开始遍历，也可以使用三叉链表
}
// n个结点的二叉链表共有n+1个空链域