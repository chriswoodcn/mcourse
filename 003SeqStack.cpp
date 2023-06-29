/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-28 07:52:53
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-29 11:13:41
 * @Description: 数据结构-栈
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
// -------------------------------------------栈的顺序存储------------------------------------------------------
// 栈是只允许在一端进行插入或删除操作的线性表
// 重要术语 栈顶 栈底 空栈 进栈 出栈 后进先出 last in first out LIFO
// 线性表需要实现的操作
// InitList(&L) 初始化表
// DestroyList(&L) 销毁操作
// ListInsert(&L,i,e) 插入操作
// ListDelete(&L,i,&e) 删除操作
// LocateElem(L,e) 按值查找
// GetElem(L,i) 按位查找
// Length() 表长
// PrintList() 输出打印
// Empty() 判空操作
// Tail() 判尾操作
// 有n个不同的元素进栈,出栈元素不同排列的个数为 $$\frac{1}{n+1} C^n_{2n}$$ 卡特兰数
// 例如 a-b-c-d-e 则合法出栈顺序有 1 / (5+1) * 10*9*8*7*6 / 5*4*3*2*1 = 42种
#include <stdio.h>
#pragma region 顺序栈
#define MaxSize 10
#define ElemType int
typedef struct
{
        ElemType data[MaxSize];
        int top;
} SqStack;
bool InitStack(SqStack &stack)
{
        stack.top = -1;
        return true;
}
void PrintStack(SqStack &stack)
{
        if (stack.top == -1)
                return;
        int len = stack.top;
        printf("SqStack: ");
        for (int i = len; i > -1; i--)
        {
                printf("%d ", stack.data[i]);
        }
        printf("\n");
}
int LengthStack(SqStack &stack)
{
        return stack.top;
}
bool EmptyStack(SqStack &stack)
{
        return stack.top == -1;
}
bool fullStack(SqStack &stack)
{
        return stack.top == MaxSize - 1;
}
bool PushStack(SqStack &stack, ElemType e)
{
        if (fullStack(stack))
                return false;
        stack.data[++stack.top] = e;
        return true;
}
bool PopStack(SqStack &stack, ElemType &e)
{
        if (EmptyStack(stack))
                return false;
        e = stack.data[stack.top--];
        return true;
}
void TestSqStack()
{
        SqStack stack;
        InitStack(stack);
        printf("%d\n", stack.top);
        PushStack(stack, 10);
        PushStack(stack, 20);
        PushStack(stack, 30);
        PushStack(stack, 40);
        PrintStack(stack);
        printf("%d\n", LengthStack(stack));
}
#pragma endregion 顺序栈
#pragma region 共享栈
typedef struct
{
        ElemType data[MaxSize];
        int top0;
        int top1;
} ShStack;
bool InitShStack(ShStack &stack)
{
        stack.top0 = -1;
        stack.top1 = MaxSize;
        return true;
}
bool PushShStack1(ShStack &stack, ElemType e)
{
        if (stack.top0 == stack.top1 - 1)
                return false;
        stack.data[++stack.top0] = e;
        return true;
}
bool PopShStack1(ShStack &stack, ElemType &e)
{
        if (stack.top0 == -1)
                return false;
        e = stack.data[stack.top0--];
        return true;
}
bool PushShStack2(ShStack &stack, ElemType e)
{
        if (stack.top1 - 1 == stack.top0)
                return false;
        stack.data[--stack.top1] = e;
        return true;
}
bool PopShStack2(ShStack &stack, ElemType &e)
{
        if (stack.top1 == MaxSize)
                return false;
        e = stack.data[stack.top1++];
        return true;
}
void PrintShStack(ShStack &stack)
{
        if (stack.top0 == -1)
                printf("ShStack1 empty");
        printf("ShStack1: ");
        for (int i = stack.top0; i > -1; i--)
        {
                printf("%d ", stack.data[i]);
        }
        printf("\n");
        if (stack.top1 == MaxSize)
                printf("ShStack2 empty");
        printf("ShStack2: ");
        for (int j = stack.top1; j < MaxSize; j++)
        {
                printf("%d ", stack.data[j]);
        }
        printf("\n");
}
void TestShStack()
{
        ShStack stack;
        InitShStack(stack);
        PushShStack1(stack, 10);
        PushShStack1(stack, 20);
        PushShStack1(stack, 30);
        PushShStack1(stack, 40);
        PushShStack1(stack, 50); // 后进先出
        PushShStack2(stack, 1000);
        PushShStack2(stack, 999);
        PushShStack2(stack, 998);
        PushShStack2(stack, 997);
        PushShStack2(stack, 996); // 后进先出
        PushShStack2(stack, 995); // 保存不进去 栈满了
        PushShStack2(stack, 994); // 保存不进去 栈满了
        PrintShStack(stack);
}
#pragma endregion 共享栈
int main()
{
        // TestSqStack();
        TestShStack();
        return 0;
}
