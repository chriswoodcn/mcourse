/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-28 07:52:53
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-07-04 16:36:36
 * @Description:
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
//
// Created by Administrator on 2022/12/18.
//
#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

void demoFormatSysOut()
{
        char A = 'A';
        int a = 1 << 15;
        uint b = 65535 * 65535;
        // 精度7位
        float c = 3.141592654789;
        // 精度15位
        double d = 3.141592654789;
        //    hd打印short
        //    hu打印u short
        //    ld打印long
        //    lu打印u long
        printf("int: %d\n", a);
        printf("int: %u\n", b);
        printf("char: %c\n", A);
        printf("float: %.8f\n", c);
        printf("double: %.8lf\n", d);
}

void demoScanf()
{
        int number = 0;
        scanf("%d", &number);
        //    printf("%d",number);
}
void printArrayInt(int *next,int len)
{
        printf("Array: ");
        for (int i = 0; i < len; i++)
        {
                printf("%d ", next[i]);
        }
        printf("\n");
}
void printArrayChar(char *next)
{
        printf("Array: ");
        for (int i = 0; i < strlen(next); i++)
        {
                printf("%c ", next[i]);
        }
        printf("\n");
}

void getNext(int *next, char *ptr)
{
        int j = -1;
        next[0] = -1;
        for (int i = 1; i < strlen(ptr); i++)
        {
                while (j > -1 && ptr[j + 1] != ptr[i])
                {
                        j = next[j];  //向前回溯 next[0]=-1 所以 j一个都没匹配到最后会等于-1
                }
                if (ptr[j + 1] == ptr[i])
                {
                        j++;
                }
                next[i] = j;
        }
}

void demoSizeOf()
{
        int a;
        // sizeof 不是函数 是一个关键字 用于测量类型的长度（字节长度）
        int b = sizeof a;
        printf("%d", b);
}

int main()
{
        // demoFormatSysOut();

        // int *p;
        // int a = 0;
        // p = &a;
        // printf("%p", p);

        char *str = "helloworldhelloworld";
        char *ptr = "owor";
        printArrayChar(str);
        int *next[strlen(ptr)];
        getNext(next, ptr);
        printArrayInt(next, strlen(ptr));
        return 0;
}
