/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-13 15:30:22
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-13 17:19:15
 * @Description: 图的操作
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
// -----------------------------------------图的基本操作----------------------------
// Adjacent(G, x, y) 判断图G是否存在边<x,y>或(x,y)
// Neighbors(G,x) 列出图G中与节点邻接的边
// InsertVertex(G,x) 在图G中插入顶点x
// DeleteVertex(G,x) 在图G中删除顶点x
// AddEdge(G,x,y) 若边<x,y>或(x,y)不存在,在图G中添加
// RemoveEdge(G,x,y) 若边<x,y>或(x,y)存在,在图G中删除
// FirstNeighbor(G,x) 找出图G中顶点x的第一个邻接点 不存在返回-1
// NextNeighbor(G,x,y) 图G中顶点y是顶点x的第一个邻接点,返回除y以外顶点x的下一个邻接顶点 不存在返回-1
// GetEdgeValue(G,x,y) 获取图G中边<x,y>或(x,y)的权值
// SetEdgeValue(G,x,y,v) 设置图G中边<x,y>或(x,y)的权值为v

// 邻接矩阵
// 无向图 Adjacent(G, x, y) G[x][y] O(1)

// 邻接表
// 无向图 Adjacent(G, x, y) 遍历G[x].first 查找有没有y  O(1~n-1)