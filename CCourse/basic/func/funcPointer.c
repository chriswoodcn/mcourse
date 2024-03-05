#include <stdio.h>
int add(int a, int b){
  return a + b;
}
int minus(int a, int b){
  return a - b;
}
int main(int argc, char* argv[])
{
  // >>>>>>>>>> 函数指针 >>>>>>>>>>
  // <数据类型> （* <函数指针名称>）（<参数说明列表>）
  int (* p)(int, int);
  p = add;
  printf("%p \n", p);
  printf("通过函数指针调用 : %d \n", (*p)(10, 20));
  p = minus;
  printf("通过函数指针调用 : %d \n", (*p)(10, 20));
  // >>>>>>>>>> 函数指针数组 >>>>>>>>>>
  int (* q[2])(int, int);
  q[0] = add;
  q[1] = minus;
  printf("通过函数指针调用 : %d \n", (*q[0])(10, 20));
  printf("通过函数指针调用 : %d \n", (*q[1])(10, 20));
  return 0;
}