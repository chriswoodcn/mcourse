/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-13 15:32:05
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-18 17:14:25
 * @Description: 图的深度优先遍历
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
// -----------------------------------------图的深度优先遍历----------------------------
#include <stdbool.h>
// 树的深度优先遍历
// 树的先根遍历
#define MaxVertxNum 100
bool visited[MaxVertxNum];
// void DFS(Graph G, int v)
// {
//         visit(v);
//         visited[v] = true;
//         for (w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
//         {
//                 if (!visited[w])
//                 {
//                         DFS(G, w);
//                 }
//         }
// }
// void DFSTraverse(Graph G)
// {
//         for (int i = 0; i < G.vexNum; i++)
//         {
//                 visited[i] = false;
//         }
//         for (int j = 0; j < G.vexNum; j++)
//         {
//                 if (!visited[j])
//                         DFS(G, j);
//         }
// }

// 空间复杂度 最坏情况递归深度O(|V|)

// DFS算法复杂度  时间复杂度=访问个节点所需时间+探索各条边所需时间
// 邻接矩阵存储的图
// 访问|V|个顶点需要O(|V|)时间 查找每个顶点的邻接点都需要O(|V|)时间 , 时间复杂度=O(|V|+|V|^2)=O(|V|^2)
// 邻接表存储的图
// 访问|V|个顶点需要O(|V|)时间 查找每个顶点的邻接点都需要O(|E|)时间 , 时间复杂度=O(|V|+2|E|)=O(|V|+|E|)
// 邻接矩阵存储的图深度遍历序列唯一
// 邻接表存储的图深度遍历序列不唯一

// 深度优先生成树

// 深度优先生成森林