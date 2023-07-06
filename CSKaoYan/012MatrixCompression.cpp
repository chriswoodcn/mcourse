/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-07-03 14:20:07
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-05 08:45:19
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
#define n 10;
int cal_subscript(int i, int j, int type)
{
    // 对称矩阵(方阵) aij = aji
    // 用一维数组存储 一维数组长度(对角线元素+下三角区数据) 1+2+3+...+n 长度为 (n+1)n/2

    // int a[(n + 1) n / 2];
    // 按下三角区行优先存储 求a_{i,j} i行j列  前面共有(i-1)行 数据个数为 1+2+3+...i-1 + j-1
    // a_{i,j} = a[i(i-1)/2 + j-1 - 1] i>=j
    // a_{i,j} = a[j(j-1)/2 + i-1 - 1] i<j时需要交换ij 因为存储的是下三角区
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
    // 按下三角区行列先存储 求a_{i,j} i行j列  前面共有(j-1)列 数据个数为 n + (n-1) + (n-2) + ... + (n-j+2) + i-j+1
    // a_{i,j} = a[(n+n-j+2)*(j-1)/2 + i-j+1] i>=j
    // i<j时需要交换ij 因为存储的是下三角区
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
    // (上/下)三角矩阵(方阵) 上（下）三角矩阵的下（上）三角（不含主对角线）中的元素均为常数。在大多数情况下，三角矩阵常数为零
    // 下三角三角矩阵行优先存储
    // int a[(n + 1) n / 2 + 1]; 多加一位存储常数
    if (type == 20001) // 下三角三角矩阵行优先存储
    {
        if (i >= j)
        {
            int len = i * (i - 1) / 2 + j - 1; // 前面数据的个数
            return len - 1;
        }
        else
        {
            return (n + 1) * n / 2; // 最后一个位置的索引
        }
    }
    // 下三角三角矩阵行列先存储
    // 求a_{i,j} i行j列  前面共有(j-1)列 数据个数为 n + (n-1) + (n-2) + ... + (n-j+2) + i-j +1
    if (type == 20002) // 下三角三角矩阵行列先存储
    {
        if (i >= j)
        {
            int len = (2n - j + 2) * (j - 1) / 2 + i - j + 1; // 前面数据的个数
            return len - 1;
        }
        else
        {
            return (n + 1) * n / 2; // 最后一个位置的索引
        }
    }
    return -1;
}
// 对角矩阵(方阵) 对角矩阵可按行优先顺序或对角线的顺序，将其压缩存储到一维数组中，且也能找到每个非零元素和向量下标的对应关系
// 当|i-j|>1时,a_{i,j} = 0
// 第一行和最后一行为 2个数据元素 共有3n-2个数据元素
// 所以压缩为一维数组之后的空间大小为 a[3n-3]
// 行有先存储a_{i,j}对应的数组下标为 当|i-j|<=1时,数组下标为[3(i-1)-1]+(j-i+2)-1
// 已知数组下标k;求对应的矩阵元素a_{i,j}
//      第k+1个元素在第几行?第几列?
//      3(i-1)-1 < k+1 <= 3i-1
//      i>=(k+2)/3
//      i = ⌈ (k+2)/3 ⌉

// 稀疏矩阵 设在mn的矩阵中有t个非零元素，令c=t/(mn),当c<=0.05时称为稀疏矩阵。
// 顺序存储 三元组<行,列,值>
// 链式存储 十字链表法  
// 行        ,        列        ,        值
// 指向同列的下一个元素 , 指向同行的下一个元素