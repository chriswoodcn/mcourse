/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-24 07:44:21
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-27 15:48:25
 * @Description: 数据结构-顺序表
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 10
#define InitSize 10
#define ElemType int
// -------------------------------------------线性表之顺序表------------------------------------------------------
// 静态顺序表
typedef struct
{
        int data[MaxSize];
        int length;
} SqList;
/**
 * @description: 初始化静态顺序表
 * @brief 初始化静态顺序表
 * @param {SqList} *L 表指针
 * @return {*}
 */
void InitList(SqList *L)
{
        for (int i = 0; i < MaxSize; i++)
        {
                L->data[i] = 0;
        }
        L->length = 0;
}
// 动态顺序表
typedef struct
{
        ElemType *data;
        int max_size;
        int length;
} SeqList2;
/**
 * @description: 初始化动态分配顺序表
 * @brief 初始化动态分配顺序表
 * @param {SeqList2} *L 表指针
 * @return {*}
 */
void InitList2(SeqList2 *L)
{
        L->data = (int *)malloc(InitSize * sizeof(ElemType));
        L->length = 0;
        L->max_size = InitSize;
}
/**
 * @description: 动态增加表长度
 * @brief 动态增加表长度
 * @param {SeqList2} *L 表指针
 * @param {int} len 增加的长度
 * @return {void}
 */
void IncreaseSize(SeqList2 *L, int len)
{
        ElemType *p = L->data;
        for (size_t i = 0; i < L->length; i++)
        {
                L->data[i] = p[i];
        }

        L->max_size = L->max_size + len;
}
/**
 * @description: 打印顺序表
 * @brief 打印顺序表
 * @param {SeqList2} *L
 * @return {void}
 */
void ListPrint(SeqList2 *L)
{
        printf("SeqList2 toString:\n");
        for (size_t i = 0; i < L->length; i++)
        {
                printf("%d\n", L->data[i]);
        }
}
/**
 * @description: 插入顺序表元素
 * @brief  插入顺序表元素
 * @param {SeqList2} *L
 * @param {int} i
 * @param {ElemType} el
 * @return {bool}
 */
bool ListInsert(SeqList2 *L, int i, ElemType el)
{
        if (i < 1)
        {
                return false;
        }
        if (L->length >= L->max_size)
        {
                IncreaseSize(L, L->max_size);
        }
        if (i <= L->length)
        {
                for (size_t j = L->length; j >= i; j--)
                {
                        L->data[j] = L->data[j - 1];
                }
                L->data[i - 1] = el;
        }
        else
        {
                L->data[L->length] = el;
        }
        L->length++;
        return true;
}
/**
 * @description: 删除顺序表元素
 * @brief 删除顺序表元素
 * @param {SeqList2} *L 顺序表指针
 * @param {int} i 位序
 * @param {int} *e 删除元素指针
 * @return {bool} 返回布尔值
 */
bool ListDelete(SeqList2 *L, int i, int *e)
{
        if (i > L->length)
        {
                return false;
        }
        ElemType el = *e;
        el = L->data[i - 1];
        for (size_t j = i; j < L->length; j++)
        {
                L->data[j - 1] = L->data[j];
        }
        L->data[L->length - 1] = 0;
        L->length--;
}
/**
 * @description: 顺序表按位查找
 * @brief 顺序表按位查找
 * @param {SeqList2} *L 表指针
 * @param {int} i 位序
 * @return {*}
 */
ElemType ListGetElm(SeqList2 *L, int i)
{
        if (i<1 | i> L->length)
        {
                return -1;
        }
        return L->data[i - 1];
}
/**
 * @description: 顺序表按值查找
 * @param {SeqList2} *L
 * @param {ElemType} e
 * @return {}
 */
int ListGetIndex(SeqList2 *L, ElemType e)
{
        for (size_t i = 0; i < L->length; i++)
        {
                if (L->data[i] == e)
                {
                        return i + 1;
                }
        }
        return 0;
}

int main()
{
        printf("顺序表\n");
        printf("InitSize: %d\n", InitSize);
        SqList L;
        InitList(&L);
        SeqList2 L2;
        InitList2(&L2);
        printf("length: %d,max_size: %d", L2.length, L2.max_size);
        ListInsert(&L2, 1, 2);
        ListInsert(&L2, 2, 3);
        ListInsert(&L2, 3, 4);
        ListInsert(&L2, 5, 10);
        ListInsert(&L2, 4, 5);
        ListPrint(&L2);
        ElemType e;
        ListDelete(&L2, 2, &e);
        ListPrint(&L2);
        return 0;
}
