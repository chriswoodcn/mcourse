/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-13 15:30:22
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-17 16:35:36
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
// 无向图/有向图 Adjacent(G, x, y) G[x][y] 算法复杂度O(1)
// 无向图 Neighbors(G,x) G[x]行或者列  算法复杂度O(|V|)
// 有向图 Neighbors(G,x) G[x]行和列 算法复杂度O(|V|)
// 无向图/有向图 InsertVertex(G,x) 直接二维数组中插入一条,初始化时就已经开辟空间 算法复杂度O(1)
// 无向图 DeleteVertex(G,x) 修改一行和一列为0 数组中为bool类型 设置为false即可 算法复杂度O(|V|)
// 有向图 DeleteVertex(G,x) 算法复杂度O(|V|)
// 无向图/有向图 AddEdge(G,x,y) G[x][y]设为1 算法复杂度O(1)
// 无向图 FirstNeighbor(G,x) 扫描G[x]行 算法复杂度O(1-|V|)
// 无向图/有向图 NextNeighbor(G,x,y) 扫描G[x]行 算法复杂度O(1-|V|)
// 无向图 GetEdgeValue(G,x,y)/SetEdgeValue(G,x,y,v) 算法复杂度O(1)   类似Adjacent,找边

// 邻接表
// 无向图/有向图 Adjacent(G, x, y) 遍历G[x].first 查找有没有y  算法复杂度O(1~|V|-1)
// 无向图 Neighbors(G,x) 遍历G[x].first 算法复杂度O(1~|V|-1)
// 有向图 Neighbors(G,x) 出边 算法复杂度O(1~|V|-1) 入边 O(|E|)
// 无向图/有向图 InsertVertex(G,x) 数组末尾插入一条,算法复杂度O(1)
// 无向图 DeleteVertex(G,x) 除了删除数组数据和指针节点外,还需要到其他数组的指针中删除对应的指针节点  算法复杂度O(1~|E|)
// 有向图 DeleteVertex(G,x) 出边 算法复杂度O(1~|V|) 入边 O(|E|)
// 无向图/有向图 AddEdge(G,x,y) 两个节点头插法插入边的指针 算法复杂度O(1)
// 无向图 FirstNeighbor(G,x) G[x].first 出边 算法复杂度O(1) 入边(基本不用) O(1~|E|)
// 无向图/有向图 NextNeighbor(G,x,y) G[x].first 出边 算法复杂度O(1) 入边(基本不用) O(1~|E|-1)
// 无向图 GetEdgeValue(G,x,y)/SetEdgeValue(G,x,y,v) 遍历G[x].first  算法复杂度O(1~|V|-1)   类似Adjacent,找边