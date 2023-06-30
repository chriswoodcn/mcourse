/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-29 15:55:52
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-30 14:50:28
 * @Description: 栈在表达式求值中的应用 p28 p29
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
using namespace std;
// -----------------------------栈在表达式求值中的应用-----------------------------------
// 三种算数表达式 中缀表达式 后缀表达式 前缀表达式

// 中缀表达式
// ① a + b
// ② a + b - c
// ③ a + b - c*d
// ④ ((15 ÷ (7-(1+1)))×3)-(2+(1+1))
// ⑤ A + B × (C - D) - E ÷ F

// 后缀表达式 (逆波兰表达式)
// ① a b +
// ② ab+ c - / a bc- +
// ③ ab+ cd* -
// ④ 15 7 1 1 + - ÷ 3 × 2 1 1 + + -
// ⑤ A B C D - × + E F ÷ - (机算结果)

// 中缀表达式 转 后缀表达式
// 手算步骤
// 步骤1： 确定中缀表达式中各个运算符的运算顺序
// 步骤2： 选择下一个运算符，按照[左操作数 右操作数 运算符]的方式组合成一个新的操作数
// 步骤3： 如果还有运算符没被处理，继续步骤2
// “左优先”原则: 只要左边的运算符能先计算，就优先算左边的 (保证运算顺序唯一)；
// 例子:
// A+B-C*D-E/F
// 从左向右 A+B-C*D+E/F
//           1 3 2 5 4
// AB+CD*-EF/+
//   1  23  45
// *****重点：中缀表达式转后缀表达式-机算
// 初始化一个栈，用于保存暂时还不能确定运算顺序的运算符。从左到右处理各个元素，直到末尾。可能遇到三种情况
// 1.遇到操作数: 直接加入后缀表达式
// 2.遇到界限符: 遇到 ‘(’ 直接入栈; 遇到 ‘)’ 则依次弹出栈内运算符并加入后缀表达式，直到弹出 ‘(’ 为止。注意: '(' 不加入后缀表达式。
// 3.遇到运算符: 依次弹出栈中优先级高于或等于当前运算符的所有运算符，并加入后缀表达式，若碰到 ‘(’ 或栈空则停止。之后再把当前运算符入栈。
#define ElemType char
typedef struct LinkNode
{
        ElemType data;
        struct LinkNode *next;
} LinkNode, *LinkStack;
bool InitStack(LinkStack &stack)
{
        LinkNode *head = (LinkNode *)malloc(sizeof(LinkNode));
        if (head == NULL)
                return false;
        head->next = NULL;
        stack = head;
        return true;
}
bool DestroyStack(LinkStack &stack)
{
        LinkNode *p = stack->next;
        while (p != NULL)
        {
                LinkNode *q = p->next;
                free(p);
                p = q;
        }
        free(stack);
        return true;
}
bool PushStack(LinkStack &stack, ElemType e)
{
        LinkNode *p = (LinkNode *)malloc(sizeof(LinkNode));
        if (p == NULL)
                return false;
        p->data = e;
        p->next = stack->next;
        stack->next = p;
        return true;
}
bool PopStack(LinkStack &stack, ElemType &e)
{
        if (stack->next == NULL)
                return false;
        e = stack->next->data;
        LinkNode *p = stack->next;
        stack->next = p->next;
        free(p);
        return true;
}
int compare_operator_prior(char a, char b)
{
        if ((a == '+' || a == '-') && (b == '+' || b == '-'))
                return 0;
        if ((a == '+' || a == '-') && (b == '*' || b == '/'))
                return -1;
        if ((a == '*' || a == '/') && (b == '*' || b == '/'))
                return 0;
        if ((a == '*' || a == '/') && (b == '+' || b == '-'))
                return 1;
        return -2;
}
char *infix_to_suffix(char *infix)
{
        if (strlen(infix) == 0)
                return NULL;
        LinkStack stack;
        InitStack(stack);
        char *p = infix;                             // 原表达式
        char *exper = (char *)malloc(strlen(p) + 1); // 转换后的表达式
        char *result = exper;
        while (*p != 0)
        {
                // printf("%c\n", *p);
                if (*p == '(')
                        PushStack(stack, *p);
                else if (*p == ')')
                {
                        while (stack->next != NULL)
                        {
                                ElemType e;
                                PopStack(stack, e);
                                if (e == '(')
                                        break;
                                *exper = e;
                                exper++;
                        }
                }
                else if (*p == '+' || *p == '-' || *p == '*' || *p == '/')
                {
                        while (stack->next != NULL && compare_operator_prior(stack->next->data, *p) >= 0)
                        {
                                if (stack->next->data == '(')
                                        break;
                                ElemType e;
                                PopStack(stack, e);
                                *exper = e;
                                exper++;
                        }
                        PushStack(stack, *p);
                }
                else
                {
                        // 遇到操作数: 直接加入后缀表达式
                        *exper = *p;
                        exper++;
                }
                p++;
        }
        while (stack->next != NULL)
        {
                ElemType e;
                PopStack(stack, e);
                *exper = e;
                exper++;
        }
        DestroyStack(stack);
        *exper = 0;
        return result;
}
// *****重点：后缀表达式的计算—机算
// 用栈实现后缀表达式的计算（栈用来存放当前暂时不能确定运算次序的操作数）
// 步骤1: 从左往后扫描下一个元素，直到处理完所有元素;
// 步骤2: 若扫描到操作数，则压入栈，并回到步骤1;否则执行步骤3;
// 步骤3: 若扫描到运算符，则弹出两个栈顶元素，执行相应的运算，运算结果压回栈顶，回到步骤1;
// 注意: 先出栈的是“右操作数”
void caculate_suffix_exper(char *suffix)
{
        if (strlen(suffix) == 0)
                return;
        // TODO
}
// 中缀表达式 转 前缀表达式
// A+B-C*D-E/F
// 从右向左 A+B-C*D+E/F
//          5 4 2 3 1
// +A-B+*CD/EF
// 5 4 32  1
void PrintExperiment(char *exper)
{
        printf("exper: ");
        while (*exper != 0)
        {
                printf("%c", *exper);
                exper++;
        }
        printf("\n");
}
int main()
{
        char *old_exper = "A+(B-C*D)+E/F";
        PrintExperiment(old_exper);
        char *new_exper = infix_to_suffix(old_exper);
        PrintExperiment(new_exper);
        return 0;
}
