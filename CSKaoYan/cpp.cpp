/*
 * @Author: chriswoodcn
 * @Email: chriswoodcn@aliyun.com
 * @Date: 2023-06-29 08:06:04
 * @LastEditors: chriswoodcn
 * @LastEditTime: 2023-06-29 09:31:34
 * @Description: c++一些知识点
 *
 * Copyright (c) 2023 by chriswoodcn, All Rights Reserved.
 */
#pragma region -----------------------------------C++函数参数传递三种方式----------------------------------
#pragma region 一. 值传递
#include <iostream>

class Node
{
public:
        Node() {}

private:
        int value;
};
// 形参是内置数据类型
void Fun(int a)
{
        std::cout << "形参a的地址 = " << &a << std::endl;
}

// 形参是类的对象
void Fun(Node node)
{
        std::cout << "形参node的地址 = " << &node << std::endl;
}

// int main()
// {
//         // 内置数据类型
//         int a = 10;
//         std::cout << "实参a的地址 = " << &a << std::endl;
//         Fun(a);
//         // 数据类型是类
//         Node node;
//         std::cout << "实参node的地址 = " << &node << std::endl;
//         Fun(node);

//         return 0;
// }
#pragma endregion 一.值传递
#pragma region 二. 指针传递
// 指针传递
void swap(int *a, int *b)
{
        std::cout << "形参指针a的地址 = " << a << std::endl;
        std::cout << "形参指针b的地址 = " << b << std::endl;
        int tmp = *a;
        *a = *b;
        *b = tmp;
}

// int main()
// {
//         int a = 5;
//         int b = 10;
//         std::cout << "实参变量a的地址 = " << &a << std::endl;
//         std::cout << "实参变量b的地址 = " << &b << std::endl;
//         std::cout << "实参变量a的值 = " << a << std::endl;
//         std::cout << "实参变量b的值 = " << b << std::endl;
//         // 调用函数，指针传递方式
//         swap(&a, &b);
//         std::cout << "实参变量a的值 = " << a << std::endl;
//         std::cout << "实参变量b的值 = " << b << std::endl;
//         getchar();
//         return 0;
// }
#pragma endregion 二.指针传递
#pragma region 三. 引用传递
// 引用实际上是某一个变量的别名，和这个变量具有相同的内存空间
// 引用传递
void Fun3(int &a)
{
        std::cout << "形参引用a的地址 = " << &a << std::endl;
        a = 100; // 对形参引用进行修改
}
// 数组的引用传递方式除了&数组名之外还要指出其长度
void Test(int (&arr)[3])
{
        arr[0] = 2;
        arr[1] = 3;
        arr[2] = 4;
}
void TestFunctionParameterPassing()
{
        int a = 10;
        std::cout << "实参a的地址 = " << &a << std::endl;
        std::cout << "实参a的值 = " << a << std::endl;
        Fun3(a);
        std::cout << "实参a的值 = " << a << std::endl;
        // getchar();
        int arr[3] = {0, 1, 2};
        Test(arr); // 直接传递数组名
        std::cout << arr[0] << std::endl;
        std::cout << arr[1] << std::endl;
        std::cout << arr[2] << std::endl;
        std::cout << "int 指针变量的字节数 = " << sizeof(int *) << std::endl;
}
#pragma endregion 三.引用传递
#pragma endregion -----------------------------------C++函数参数传递三种方式----------------------------------
int main()
{
        int a = 10;
        // 引用必须声明时就要有初始化;
        // 引用初始化的变量一定要能取地址;
        // 引用是不可改变的;
        int &b = a;
        int *c = &a;
        // 上述代码的反汇编 两者处理方式一致，都是将a内存单元的地址放到b/c内存单元中去
        printf("a的地址: %p a的值: %d\n", &a, a); // a的地址: 000000000061fe14 a的值: 10
        printf("b的地址: %p b的值: %d\n", &b, b); // b的地址: 000000000061fe14 b的值: 10
        printf("c的地址: %p c的值: %d c的解引用: %d\n", &c, c, *c); // c的地址: 000000000061fe08 c的值: 6422036 c的解引用: 10
        return 0;
}
