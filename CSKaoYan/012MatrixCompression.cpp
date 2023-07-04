/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-03 14:20:07
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-04 21:20:42
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
// 用一维数组存储 一维数组长度(对角线元素+下三角区数据) 1+2+3+...+n 长度为 (n+1)n/2

// int a[(n + 1) n / 2];
// 按下三角区行优先存储 求a_{i,j} i行j列  前面共有(i-1)行 数据个数为 1+2+3+...i-1 + j-1
// a_{i,j} = a[i(i-1)/2 + j-1 - 1] i>=j
// a_{i,j} = a[j(j-1)/2 + i-1 - 1] i<j时需要交换ij 因为存储的是下三角区
int cal_subscript(int i, int j, int type)
{
    if (type == 10001) // 对称矩阵下三角区行优先存储
    {
        if (i >= j)
        {
            int len = i(i - 1) / 2 + j - 1; // 前面数据的个数
            return len - 1;
        }
        else
        {
            int len = j(j - 1) / 2 + i - 1; // 交换i和j位置,前面数据的个数
            return len - 1;
        }
    }
    if (type == 10002) // 对称矩阵下三角区列优先存储
    {
        if (i >= j)
        {
            int len = (n + n - j + 2) * (j - 1) / 2 + i - j + 1; // 前面数据的个数
            return len - 1;
        }
        {
            int len = (n + n - i + 2) * (i - 1) / 2 + j - i + 1; // 前面数据的个数
            return len - 1;
        }
    }
    return -1;
}
// 按下三角区行列先存储 求a_{i,j} i行j列  前面共有(j-1)列 数据个数为 (n-1+1) + (n-2+1) + (n-3+1) + ... + (n-(j-1)+1) + i-j+1
// (n+n-j+2)*(j-1)/2 + i-j+1
// (上/下)三角矩阵(方阵) 上（下）三角矩阵的下（上）三角（不含主对角线）中的元素均为常数。在大多数情况下，三角矩阵常数为零

// 对角矩阵(方阵) 对角矩阵可按行优先顺序或对角线的顺序，将其压缩存储到一维数组中，且也能找到每个非零元素和向量下标的对应关系

// 稀疏矩阵 设在mn的矩阵中有t个非零元素，令c=t/(mn),当c<=0.05时称为稀疏矩阵。