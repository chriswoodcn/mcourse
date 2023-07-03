/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-03 14:20:07
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-03 14:32:26
 * @Description: 特殊矩阵的压缩存储 p32
 * 
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved. 
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
using namespace std;
#define ElemType int;
// -----------------------------特殊矩阵的压缩存储-----------------------------------
// 矩阵定义： 一个由m*n个元素排成的m行(横向)n列(纵向)的表。
// 数组的存储结构
// 一维数组
ElemType a[10];
// 起始地址：LOC
// 数组元素 a[i] 的存放地址 = LOC + i × sizeof(ElemType)
// 二维数组
ElemType b[2][3];
// 起始地址：LOC
// M行N列的二维数组 b[M][N] 中，b[i][j]的存储地址：
// 行优先存储: LOC + (i×N + j) × sizeof(ElemType)
// 列优先存储：LOC + (j×M + i) × sizeof(ElemType)

// 特殊矩阵——压缩存储空间（只存有用的数据）
// 对称矩阵(方阵) aij = aji
// (上/下)三角矩阵(方阵) 上（下）三角矩阵的下（上）三角（不含主对角线）中的元素均为常数。在大多数情况下，三角矩阵常数为零
// 对角矩阵(方阵) 对角矩阵可按行优先顺序或对角线的顺序，将其压缩存储到一维数组中，且也能找到每个非零元素和向量下标的对应关系
// 稀疏矩阵 设在mn的矩阵中有t个非零元素，令c=t/(mn),当c<=0.05时称为稀疏矩阵。