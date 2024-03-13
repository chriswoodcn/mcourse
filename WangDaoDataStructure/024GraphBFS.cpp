/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-13 15:31:48
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-18 16:45:41
 * @Description: 图的广度优先遍历
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
// -----------------------------------------图的广度优先遍历----------------------------
#include <stdbool.h>
// 树的广度优先遍历
// 1.若树非空,则根结点入队
// 2.若队列非空,w队头元素出队并访问,同时将该元素的孩子依次入队
// 3.重复2直到队列为空
// 图的广度优先遍历
// 1.找到与一个顶点相邻的所有顶点
// 2.标记哪些顶点被访问过
// 3.需要一个辅助队列

// FirstNeighbor(G,x)
// NextNeighbor(G,x,y)
#define MaxVertxNum 100
bool visited[MaxVertxNum];
// void BFS(Graph G, int v)
// {
//         visit(v);  //访问初始顶点v
//         visited[v] = true;  //对v做已访问标记
//         Enqueue(Q, v);  //顶点v入队列Q
//         while (!isEmpty(Q))
//         {
//                 Dequeue(Q, v);  //顶点v出队列
//                 for (w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
//                 {
//                       //检测v所有邻接点
//                         if (!visited[w])
//                         {
//                                 visit(w); //访问顶点w
//                                 visited[v] = true; //对w做已访问标记
//                                 Enqueue(Q, w);  //顶点w出队列
//                         }
//                 }
//         }
// }
// void BFSTraverse(Graph G)
// {
//         for (int i = 0; i < G.vexNum; i++)
//         {
//                 visited[i] = false;
//         }
//         InitQueue(Q);
//         for (int i = 0; i < G.vexNum; i++)
//         {
//                 if (!visited[i])
//                         BFS(G, i);
//         }
// }

// 空间复杂度 最坏情况递归深度O(|V|)

// BFS算法复杂度  时间复杂度=访问个节点所需时间+探索各条边所需时间
// 邻接矩阵存储的图
// 访问|V|个顶点需要O(|V|)时间 查找每个顶点的邻接点都需要O(|V|)时间 , 时间复杂度=O(|V|+|V|^2)=O(|V|^2)
// 邻接表存储的图
// 访问|V|个顶点需要O(|V|)时间 查找每个顶点的邻接点都需要O(|E|)时间 , 时间复杂度=O(|V|+2|E|)=O(|V|+|E|)
// 邻接矩阵存储的图广度遍历序列唯一
// 邻接表存储的图广度遍历序列不唯一

// 广度优先生成树

// 广度优先生成森林