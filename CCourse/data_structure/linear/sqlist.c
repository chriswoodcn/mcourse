//
// Created by wyg on 2024/3/7.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sqlist.h"

/**
 * 创建顺序表
 * @return sqlist_p 顺序表指针的值
 */
sqlist_p create()
{
    sqlist_p l = (sqlist_p)malloc(sizeof(sqlist));
    if (l == NULL)
    {
        printf("sqlist malloc failed\n");
        return l;
    }
    memset(l, 0, sizeof(sqlist));
    l->last = -1;
    return l;
}

/**
 * 清空順序表
 * @param l 顺序表指针的值
 * @return 1 成功 0 失败
 */
int clear(sqlist_p l)
{
    if (l == NULL)
    {
        printf("sqlist is NULL\n");
        return 0;
    }
    memset(l, 0, sizeof(sqlist));
    l->last = -1;
    return 1;
}

/**
 * 是否为空
 * @param l 顺序表指针的值
 * @return 1 是 0 否
 */
int empty(sqlist_p l)
{
    if (l == NULL)
    {
        printf("sqlist is NULL\n");
        return 1;
    }
    return l->last > -1 ? 0 : 1;
}

/**
 * 顺序表长度
 * @param l 顺序表指针的值
 * @return 长度
 */
int length(sqlist_p l)
{
    if (l == NULL)
    {
        printf("sqlist is NULL\n");
        return 0;
    }
    return l->last + 1;
}

/**
 * 元素的位置
 * @param l 顺序表指针的值
 * @param d 元素
 * @return 位置 -1 不存在
 */
int locate(sqlist_p l, data_t d)
{
    if (l == NULL)
    {
        printf("sqlist is NULL\n");
        return -1;
    }
    if (l->last == -1)
        return -1;
    int i = 0;
    while (i < l->last + 1)
    {
        if (l->data[i] == d)
            break;
        i++;
    }
    return i;
}

/**
 * 插入元素
 * @param l 顺序表指针的值
 * @param d 元素
 * @param pos 位置
 * @return 1 成功 0 失败
 */
int insert(sqlist_p l, data_t d, int pos)
{
    if (l == NULL)
    {
        printf("sqlist is NULL\n");
        return 0;
    }
    if (l->last == sqlist_max_len - 1)
    {
        printf("sqlist is full\n");
        return 0;
    }
    if (pos < 0 || pos > l->last + 1)
    {
        printf("pos is invalid, must between 0 and %d\n", l->last + 1);
        return 0;
    }
    // 0 0
    if (pos <= l->last) 
    {
        // 已有数据全部向后移动一位,从后向前顺序
        int index = l->last;
        while (index >= pos)
        {
            l->data[index + 1] = l->data[index];
            index--;
        }
    }
    // pos位置赋值
    l->data[pos] = d;
    l->last = l->last + 1;
    return 1;
}
void show(sqlist_p l)
{
    if (l == NULL)
    {
        printf("sqlist is NULL\n");
    }
    printf(">>>>>>>>>> sqlist show start >>>>>>>>>>\n");
    for (int i = 0; i <= l->last; i++)
    {
        printf("%d-----%d\n", i, l->data[i]);
    }
    printf(">>>>>>>>>> sqlist show end >>>>>>>>>>\n");
}