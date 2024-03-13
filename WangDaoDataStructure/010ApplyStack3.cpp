/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-29 15:55:52
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-30 15:18:03
 * @Description: 栈在递归中的应用 p30
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
using namespace std;
// -----------------------------栈在递归中的应用-----------------------------------
// 函数调用的特点：最后被调用的函数最先执行结束(LIFO) last in first out

// 函数调用时，需要用一个栈存储：
// 调用返回地址
// 实参
// 局部变量

// 递归调用时，函数调用栈称为 “递归工作栈”:
// 每进入一层递归，就将递归调用所需信息压入栈顶；
// 每退出一层递归，就从栈顶弹出相应信息；

// 缺点：太多层递归可能回导致栈溢出；
// 适合用“递归”算法解决：可以把原始问题转换为属性相同，但规模较小的问题；
int main()
{
        return 0;
}
