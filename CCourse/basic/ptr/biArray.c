#include <stdio.h>

int main()
{
  // >>>>>>>>>> 指针和二维数组 >>>>>>>>>>
  int a[3][2] = {{1,2},{5,6},{8,9}};
  int n = sizeof(a) / sizeof(int);
  printf("size: %d \n",n);
  // 一级指针遍历二维数组
  // int *p = a;
  // int *p = &a[0][0];
  int *p = a[0];
  for (size_t i = 0; i < n; i++)
  {
    /* code */
    printf("%d \n",*(p+i));
  }
  // *(a+1) === a[1] 二维数组名a 代表行地址常量
  printf("a[1] address = %p \n",a[1]);
  printf("a address = %p  a+1 address = %p \n", a, a+1); //相差8字节
  printf("a[0] address = %p  a[0]+1 address = %p \n", a[0], a[0]+1); //相差4字节
  printf("*(a+1) address = %p \n",*(a+1));
  printf("*(a+1)[0] = %d \n",*(a+1)[0]);

  //声明行指针
  int (*p2)[2];
  p2 = a;
  printf("p2 %p \n",p2);
  return 0;
}