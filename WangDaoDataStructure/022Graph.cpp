/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-12 16:47:31
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-13 14:56:29
 * @Description: 图 p55~58
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
// ----------------------------------图的基本概念---------------------------------------
// 图G由顶点集V和边集E组成 G=(V,E)
// V(G)表示图G中顶点的有限非空集;E(G)表示图G中顶点之间的关系集合
// 若V={V1,V2...Vn} 则用|V|表示图G中顶点的个数 也称图G的阶
// E={(u,v)|u∈V,v∈V} 用|E|表示图G中边的条数
// 线性表可以是空表 树可以是空树 图不可以是空 V肯定是非空集

// 无向图 有向图
// 若E是无向边的有限集合;图G为无向图 (v,w) = (w,v)
// 例如 G1=(V1,E1)
// V1 = {A,B,C,D,E}
// E1 = {(A,B),(B,D),(B,E),(C,D),(C,E),(D,E)}
// 若E是有向边的有限集合;图G为有向图 <v,w> ≠ <w,v>
// 例如 G2=(V2,E2)
// V1 = {A,B,C,D,E}
// E1 = {<A,B>,<A,C>,<A,D>,<A,E>,<B,A>,<B,C>,<B,E>,<C,D>}

// 简单图 多重图
// 简单图 1.不存在重复边 2.不存在顶点到自身的边
// 多重图 某两个节点之间的边数多于一条 允许顶点通过同一条边和自己关联

// 顶点的度/入度/出度
// 无向图: 顶点v的度是指该顶点的边的条数TD(v)  ∑TD(v) = 2|E|
// 有向图:
//    入度:顶点v为终点的有向边的条数ID(v)
//    出度:顶点v为起点的有向边的条数OD(v)
//    顶点的度: 入度+出度     ∑ID(v)=∑OD(v)=|E|

// 顶点-顶点关系描述
// 1.路径 顶点Vp到顶点Vq之间的一条路径是指顶点序列,Vp,Vi1...Vin,Vq
// 2.回路 第一个顶点和最后一个顶点相同的路径称为回路或环
// 3.简单路径 路径序列中顶点不重复出现的称为简单路径
// 4.简单回路 除了第一个和最后一个,顶点不重复出现的回路称为简单回路
// 5.路径长度 路径上边的数量
// 6.点到点的距离 从顶点p到顶点q的最短路径若存在,,此路径长度称为pq的距离,若不存在路径,则记为无穷∞
// 7.连通
//    无向图: 顶点p到顶点q有路径存在,pq连通
//    有向图: 顶点p到q q到p都有路径 pq强连通

// 连通图
// 图G中任意两个顶点都是连通的,图G为连通图,否则为非连通图
//   若n个顶点的无向图G,如果G是连通图,则最少有n-1条边
//                     如果G是非连通图,则最多可能有C_{n-1}^2条边 即(n-1)(n-2)/2
// 图G中任何一对顶点都是强连通的,图G为强连通图
//   若n个顶点的有向图G,如果G是强连通图,则最少有n条边(形成回路)

// 子图
// 两个图G=(v,e) G'=(v',e') v'是v的子集 e'是e的子集 则G'是G的子图
// 若有满足V(G')=V(G)的子图G' 则G'为G的生成子图

// 连通分量
// 无向图中的极大连通子图称为连通分量
// 强连通分量
// 有向图中的极大强连通子图称为强连通分量

// 生成树
// 连通图的生成树是包含图中全部顶点的一个极小连通子图(边尽可能少,但要保持连通)
// 生成森林
// 非连通图中,连通分量的生成树,构成了非连通图的生成森林

// 边的权 带权图/网
// 边的权  一个图中,每条边标上具有某种含义的数值,该数值称为边的权值
// 带权图/网  边上带有权值的图称为带权图,也称网
// 带权路径长 带权图上一条路径上所有权值的和称为该路径的带权路径长

// 几种特殊形态的图
// 1.无向完全图  无向图中任意两个顶点连通 C_n^2 条边
// 2.有向完全图  有向图中任意两个顶点强连通 2C_n^2条弧
// 3.边数很少的图  稀疏图  一般来说|E|<|V|log|V|    反之稠密图
// 4.树  不存在回路,且连通的无向图 反之森林
// 5.有向树  一个顶点入度为0 其余顶点入度为1的有向图

//  ----------------------------------邻接矩阵法---------------------------------------
// 顺序存储
// 使用二维数组存储 矩阵表示
// Aij = 1 (vi,vj)或<vi,vj>是边或弧
// Aij = 0 (vi,vj)或<vi,vj>不是边或弧
#define MaxVertxNum 100
typedef struct
{
  char Vex[MaxVertxNum];              // 顶点表
  int Edge[MaxVertxNum][MaxVertxNum]; // 邻接矩阵,边
  int vexNum, arcNum;                 // 图的顶点数,边数
} MGraph;
// 无向图:顶点i的度 ∑Edge[i][0-n]或者∑Edge[0-n][i]
// 有向图:顶点i的度 入度 + 出度
// 有向图:入度 ∑Edge[0-n][i]
// 有向图:出度 ∑Edge[i][0-n]

// 空间复杂度 O(n^2)
// 无向图可以使用对称矩阵压缩存储

// 邻接矩阵的性质
// 邻接矩阵A(矩阵元素为1/0) A^n[i][j] = 顶点i到顶点j的长度为n的路径数目
// 例子
//    A B C D
// A  0 1 0 0
// B  1 0 1 1
// C  0 1 0 1
// D  0 1 1 0
// A^2[1][4] = a11*a14 + a12*a24 + a13*a34 + a14*a44 = 1  A-D路径长度为2的路径有1条
// A^2[2][2] = a21*a12 + a22*a22 + a23*a32 + a24*a42 = 3  B-B路径长度为2的路径有3条
// ----------------------------------邻接表法---------------------------------------
// 顺序+链式存储
// 边 / 弧
typedef struct ArcNode
{
  int adjVex;           // 边 / 弧指向哪一个节点
  struct ArcNode *next; // 下一条边 / 弧的指针
  // InfoType info;  //边权值
} ArcNode;
// 顶点
#define VertexType char
typedef struct VNode
{
  VertexType Data; // 顶点信息
  ArcNode *first;  // 第一条边 / 弧
} VNode, AdjList[MaxVertxNum];
// 邻接表存储的图
typedef struct
{
  AdjList vertices;
  int vexNum, arcNum;
} ALGraph;

// 空间复杂度
// 无向图 O(|V|+2|E|)
// 有向图 O(|V|+|E|)

// 无向图:顶点的度 顶点的ArcNode个数
// 有向图:顶点的度 出度 + 入度
// 有向图:出度 顶点的ArcNode个数
// 有向图:入度 不好计算 遍历寻找
// ----------------------------------十字链表---------------------------------------
// 只用于存储有向图
// 弧节点
typedef struct CArcNode
{
  int headVex;            // 弧头编号
  int tailVex;            // 弧尾编号
  struct CArcNode *hlink; // 弧头相同的下一条弧
  struct CArcNode *tlink; // 弧尾相同的下一条弧
  // InfoType info;  //边权值
} CArcNode;
typedef struct CVNode
{
  VertexType Data;    // 顶点信息
  CArcNode *firstIn;  // 弧头为此顶点第一条弧
  CArcNode *firstOut; // 弧尾为此顶点第一条弧
} CVNode, CAdjList[MaxVertxNum];
// 十字链表存储的有向图
typedef struct
{
  CAdjList vertices;
  int vexNum, arcNum;
} CALGraph;
// 空间复杂度 O(|V|+|E|) 没有入度不好计算的缺点

// ----------------------------------邻接多重表---------------------------------------
// 只用于存储无向图
// 边节点
typedef struct MArcNode
{
  int i;                  // 顶点编号
  int j;                  // 顶点编号
  struct MArcNode *ilink; // 依附于顶点i的下一条边
  struct MArcNode *jlink; // 依附于顶点j的下一条边
  // InfoType info;  //边权值
} MArcNode;
typedef struct MVNode
{
  VertexType Data; // 顶点信息
  MArcNode *first; // 依附于顶点的第一条边
} MVNode, MAdjList[MaxVertxNum];
// 邻接多重表存储的无向图
typedef struct
{
  MAdjList vertices;
  int vexNum, arcNum;
} MALGraph;

// 空间复杂度 O(|V|+|E|) 同时删除节点和边也很方便