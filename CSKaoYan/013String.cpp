/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-30 15:28:01
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-30 16:37:49
 * @Description: 串的定义和实现
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
using namespace std;
// -----------------------------串的定义和实现-----------------------------------
// 串: 零个或多个字符组成的有限序列，如 S = 'iPhone 14 Pro Max?';
// 串名：S是串名；
// 串的长度：串中字符的个数n；
// 空串：n=0时的串；
// 子串：串中任意多个连续的字符组成的子序列称为该串的子串；
// 主串：包含所有子串的串；
// 字符在主串中的位置：某个字符在串中的序号（从1开始）；
// 子串在主串中的位置：子串的第一个字符在主串中的位置；
// 空串 V.S 空格串：M = ‘’ 是空串；N = ’ ’ 是空格串；
// 串 V.S 线性表：
// 串是特殊的线性表，数据元素之间呈线性关系（逻辑结构相似）；
// 串的数据对象限定为字符集：中文字符、英文字符、数字字符、标点字符…
// 串的基本操作，如增删改查通常以子串为操作对象

// 串的基本操作
// StrAssign(&T, chars): 赋值操作，把串T赋值为chars；
// StrCopy(&T, S): 复制操作，把串S复制得到串T
// StrEmpty(S): 判空操作，若S为空串，则返回TRUE，否则返回False；
// StrLength(S): 求串长，返回串S的元素个数；
// ClearString(&S): 清空操作，将S清为空串；
// DestroyString(&S): 销毁串，将串S销毁——回收存储空间；
// Concat(&T, S1, S2): 串联联接，用T返回由S1和S2联接而成的新串———可能会导致存储空间的扩展；
// SubString(&Sub, S, pos, len): 求子串，用Sub返回串S的第pos个字符起长度为len的子串；
// Index(S, T): 定位操作，若主串S中存在与串T值相同的子串，则返回它再主串S中第一次出现的位置，否则函数值为0；
// StrCompare(S, T): 串的比较操作，参照英文词典排序方式；若S > T,返回值>0; S = T,返回值=0 (需要两个串完全相同) ; S < T,返回值<0;

// 串的存储结构
// 定长顺序分配存储表示
#define MAXLEN 255 // 预定义最大串长为255

typedef struct
{
        char ch[MAXLEN]; // 静态数组实现（定长顺序存储）
                         // 每个分量存储一个字符
                         // 每个char字符占1B
        int length;      // 串的实际长度
} SString;
// 串长的两种表示法：
// 方案一：用一个额外的变量length来存放串的长度（保留ch[0]）；
// 方案二：用ch[0]充当length；  优点：字符的位序和数组下标相同；
// 方案三：没有length变量，以字符’\0’表示结尾（对应ASCII码的0）；  缺点：需要从头到尾遍历；
// 方案四——最终使用方案：ch[0]废弃不用，声明int型变量length来存放串的长度（方案一与方案二的结合）

bool StrAssign(SString &T, char *str)
{
        if (str == NULL)
                return false;
        int i = 1;
        while (*str != 0)
        {
                T.ch[i] = *str;
                i++;
                str++;
        }
        T.length = i - 1;
        return true;
}
void StrPrint(SString &s)
{
        if (s.length == 0)
                cout << "SString Empty" << endl;
        cout << "SString length: " << s.length << endl;
        int i = 1;
        while (i <= s.length)
        {
                cout << s.ch[i++];
        }
        cout << endl;
}
// 1. 求子串
bool SubString(SString &Sub, SString &S, int pos, int len)
{
        // 子串范围越界
        if (pos + len - 1 > S.length)
                return false;

        for (int i = pos; i < pos + len; i++)
                Sub.ch[i - pos + 1] = S.ch[i];

        Sub.length = len;

        return true;
}
// 2. 比较两个串的大小
int StrCompare(SString &S, SString &T)
{
        for (int i; i < S.length && i < T.length; i++)
        {
                if (S.ch[i] != T.ch[i])
                        return S.ch[i] - T.ch[i];
        }
        // 扫描过的所有字符都相同，则长度长的串更大
        return S.length - T.length;
}
// 3. 定位操作
int Index(SString S, SString T)
{
        int i = 1;
        int n = S.length;
        int m = T.length;
        SString sub; // 用于暂存子串

        while (i <= n - m + 1)
        {
                SubString(sub, S, i, m);
                if (StrCompare(sub, T) != 0)
                        ++i;
                else
                        return i; // 返回子串在主串中的位置
        }
        return 0; // S中不存在与T相等的子串
}
void TestSString()
{
        SString S, T;
        char *str = "iPhone 14 Pro Max?";
        StrAssign(S, str);
        StrPrint(S);
        StrAssign(T, str);
        StrPrint(T);
        printf("%d\n", StrCompare(S, T));
        printf("%d\n", Index(S, T));
}
// 堆分配存储表示
typedef struct
{
        char *ch;   // 按串长分配存储区，ch指向串的基地址
        int length; // 串的长度
} HString;
bool HStrDestroy(HString &S)
{
        S.length = 0;
        free(S.ch);
        return true;
}
bool HStrAssign(HString &S, char *str)
{
        if (str == NULL)
                return false;
        int len = strlen(str);
        char *copy = (char *)malloc(len * sizeof(char));
        S.ch = copy;
        S.length = len;
        while (*str != 0)
        {
                *copy = *str;
                copy++;
                str++;
        }
        return true;
}
void HStrPrint(HString &S)
{
        if (S.length == 0)
                cout << "HString Empty" << endl;
        cout << "HString length: " << S.length << endl;
        int i = 1;
        while (i <= S.length)
        {
                cout << S.ch[i++];
        }
        cout << endl;
}
void TestHString()
{
        HString S, T;
        char *str = "iPhone 14 Pro Max?";
        HStrAssign(S, str);
        HStrPrint(S);
        HStrAssign(T, str);
        HStrPrint(T);
        HStrDestroy(S);
        HStrDestroy(T);
}
// 串的链式存储
typedef struct StringNode
{
        char ch; // 每个结点存1个字符
        struct StringNode *next;
} StringNode, *String;
// 问题：存储密度低，每个字符1B，每个指针4B；
// 解决方案：每一个链表的结点存储多个字符——每个结点称为块——块链结构
typedef struct StringNodePro
{
        char ch[4]; // 每个结点存多个个字符
        struct StringNodePro *next;
} StringNodePro, *StringPro;
// 结合链表思考优缺点
// 存储分配角度：链式存储的字符串无需占用连续空间，存储空间分配更灵活；
// 操作角度：若要在字符串中插入或删除某些字符，则顺序存储方式需要移动大量字符，而链式存储不用；
// 若要按位序查找字符，则顺序存储支持随机访问，而链式存储只支持顺序访问；

// ---------------------------------------------串的模式匹配---------------------------------------------------
// 模式匹配：子串的定位操作称为串的模式，它求的是子串（常称模式串）在主串中的位置。

int main()
{

        printf("%d\n", sizeof(void *));
        TestHString();
        return 0;
}
