/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-28 07:52:53
 * @LastEditors: chriswoodcn chriswoodcn@aliyun.com
 * @LastEditTime: 2023-06-28 17:27:41
 * @Description: 数据结构-栈
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
// -------------------------------------------线性表-栈------------------------------------------------------
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
#define MaxSize 10
#define ElemType int
typedef struct
{
        ElemType data[MaxSize];
        int top;
} SqStack;
bool IintStack(SqStack *s)
{
        SqStack s;
        *s = s;
        s.top = 0;
        return true;
}
void TestSqStack()
{
        SqStack stack;
        InitStack(&stack);
}

int main()
{
        
        return 0;
}
