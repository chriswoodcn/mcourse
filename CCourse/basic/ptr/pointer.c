#include <stdio.h>

int main()
{
  // >>>>>>>>>> 指针的基本使用 >>>>>>>>>>
  void* p0;
  int a = 10;
  p0 = &a;
  printf("p0 ref address: %p\n", p0);
  printf("p0 ref value: %d\n", *(int*)p0);
  printf("p0 real address: %p\n", &p0);
  printf("p0 size: %d\n", sizeof(p0));

  // >>>>>>>>>> 指针的运算 >>>>>>>>>> + - ++ --
  // px + n 大n个数据 步长和px的指针类型有关
  // 关系运算 可以和零进行等于不等于关系运算 判断指针是否为空
  void* p1 = NULL;//((Void*)0)
  void* p2 = (void*)0;//((Void*)0)
  void* p3;
  printf("p1 ref address: %p\n", p1);//初始化之后才为0
  printf("p2 ref address: %p\n", p2);
  printf("p3 ref address: %p\n", p3);

  // >>>>>>>>>> 指针与数组 >>>>>>>>>>
  int arr[] = {1,2,3,4,5,6,7,8,9,0}; //arr是地址常量不能改变 但能参与运算
  int *p,n;
  p = arr;
  n = sizeof(arr) / sizeof(int);
  for (size_t i = 0; i < n; i++)
  {
    printf("%d ",arr[i]);
  }
  puts("");
  for (size_t i = 0; i < n; i++)
  {
    printf("%d ",*(p+i));
  }
  puts("");
  for (size_t i = 0; i < n; i++)
  {
    printf("%d ",p[i]);
  }
  puts("");
  for (size_t i = 0; i < n; i++)
  {
    printf("%d ",*(arr+i));
  }
  puts("");
  return 0;
}