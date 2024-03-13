/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-11 14:00:47
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-11 15:18:59
 * @Description: 树的存储结构/树森林的遍历 p50~51
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
//------------------------------------------树的存储结构-----------------------------------------------------------
// 双亲表示法
// 顺序存储
#define Max_Size 100
typedef struct PTNode
{
  char data;  // 数据
  int parent; // 双亲的下标
} PTNode;
typedef struct
{
  PTNode nodes[Max_Size];
  int size;
} PTTree;
PTTree t;
t.size = 0;
t.nodes[0] = {'a', -1};
t.nodes[1] = {'b', 0};
t.nodes[2] = {'c', 0};
t.nodes[3] = {'d', 0};
t.nodes[4] = {'e', 1};
t.nodes[5] = {'f', 1};
t.nodes[6] = {'g', 2};
t.nodes[7] = {'h', 3};
t.nodes[8] = {'i', 3};
t.nodes[9] = {'j', 3};
t.nodes[10] = {'k', 4};
t.size = 11;
// 孩子表示法
// 顺序+链式存储
struct CTNode
{
  int child;
  struct CTNode *next;
};
typedef struct
{
  int data;
  struct CTNode *firstChild;
} CTBox;
typedef struct
{
  CTBox nodes[Max_Size];
  int n, r; // 节点数和根的位置
} CTree;
// ***孩子兄弟表示法
// 链式存储
typedef struct CSNode
{
  int data;                               // 数据域
  struct CSNode *fistChild, *nextSibling; // 第一个孩子和右兄弟指针
} CSNode, *CSTree;

// 树 森林 二叉树的转换
// 1.树和二叉树的转换  
// 树用孩子兄弟表示法后 转换成二叉树 当然也可以把孩子兄弟表示法的二叉树再转换成树
// 2.森林和二叉树的转换  
// 森林同级的树看成是兄弟级 用孩子兄弟表示法后 转换成二叉树 当然也可以把孩子兄弟表示法的二叉树再转换成森林

//-------------------------------------------树森林的遍历--------------------------------------------------------
// 1.树的先根遍历
// 若树非空,先访问根结点,再依次对每颗子树进行先根遍历
// = 转换成二叉树的先序遍历
// 2.树的后根遍历
// 若树非空,先依次对每棵子树进行后根遍历,最后再访问根节点
// = 转换成二叉树的中序遍历***
// 3.树的层次遍历
// 若树非空,根结点入队
// 若队列非空,队头元素出队并访问,同时将该元素的孩子依次入队
// 重复2直到队列为空


// 1.森林的先序遍历
// 若森林非空,访问森林中的第一棵树的根结点
// 先序遍历第一棵树中根结点的子树森林
// 先序遍历除去第一棵树之后剩余的树构成的森林
// = 依次对各子树进行先根遍历
// = 转换成二叉树的先序遍历
// 2.中序遍历森林
// 若森林非空,中序遍历森林中的第一棵树的根结点的子树森林
// 访问第一棵树的根节点
// 中序遍历除去第一棵树之后剩余的树构成的森林
// = 依次对各子树进行后根遍历
// = 转换成二叉树的中序遍历

//           树                森林                二叉树
//         先根遍历           先序遍历            先序遍历
//         后根遍历           中序遍历            中序遍历
