/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-11 15:41:19
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-11 17:01:28
 * @Description: 并查集 p53~54
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
//-----------------------------------------并查集-----------------------------------------------------
// 逻辑结构-集合
// 数据之间的逻辑关系
// 1.集合
// 2.线性结构
// 3.树形结构
// 4.图形结构
#include <cstdio>
// 树-双亲表示法  并 查 集合操作方便
#define ELemType int
#define Max_Size 100
typedef struct PTNode
{
        ELemType data; // 数据
        int parent;    // 双亲的下标
} PTNode;
typedef struct
{
        PTNode nodes[Max_Size];
        int size;
} PTTree;
void inputData(PTTree *tree)
{
        int x;
        scanf("%d", &x);
        int i = 0;
        PTNode node;
        node.parent = -1;
        node.data = x;
        (*tree).nodes[i] = node;
        (*tree).size = i + 1;
        while (x != 999)
        {
                i++;
                scanf("%d", &x);
                PTNode node;
                node.parent = i - 1;
                node.data = x;
                (*tree).nodes[i] = node;
                (*tree).size = i + 1;
        }
}
void printData(PTTree *tree)
{
        int size = (*tree).size;
        while (size != 0)
        {
                size--;
                printf("elem >>> addr:%p pIndex:%d val:%d index:%d\n",
                       &((*tree).nodes[size]),
                       (*tree).nodes[size].parent,
                       (*tree).nodes[size].data,
                       size);
        }
}
#define SIZE 13
void Initial(int S[])
{
        for (int i = 0; i < SIZE; i++)
        {
                S[i] = -1;
        }
}
// 查操作,返回x下标元素所属集合(返回根节点的下标)
int Find(int S[], int x)
{
        while (S[x] >= 0)
        {
                x = S[x];
        }
        return x;
}
// 并操作,2个集合合并为1个 将根root2连接到root1下
void Union(int S[], int root1, int root2)
{
        if (root1 == root2)
                return;
        // S[root2] = root1;
        if (S[root2] >= S[root1]) // root2节点更少
        {
                S[root1] += S[root2]; // 累加节点总数
                S[root2] = root1;     // 小树合并到大树
        }
        else
        {
                S[root2] += S[root1]; // 累加节点总数
                S[root1] = root2;     // 小树合并到大树
        }
}
//-----------------------------------------并查集的优化-----------------------------------------------------
// find操作优化 压缩路径
// find查操作优化,先找到根结点,再进行压缩路径
int FindPro(int S[], int x)
{
        int root = x;
        while (S[root] > 0)
                root = S[root]; // 循环找到根结点
        while (x != root)       // 压缩路径
        {
                int t = S[x]; // t指向x的父节点
                S[x] = root; // x直接挂到根结点下
                x = t;
        }
        return root; // 返回根节点
}
// 查找的算法复杂度从n 降低到 log2N 再降低到 α(N) 对于常数级别的N来说 α(N)<=4
// 合并的算法复杂度从n2 降低到 Nlog2N 再降低到 Nα(N)

int main()
{
        PTTree tree;
        inputData(&tree);
        printData(&tree);
        return 0;
}