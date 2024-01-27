#include <stdio.h>
int factorial(int num);
int fib(int num);

int main()
{
  // >>>>>>>>>> 递归函数 >>>>>>>>>>
  printf("5 factorial value = %d \n",factorial(5));
  printf("5 fib value = %d \n",fib(5)); //1 1 2 3 5 8
  return 0;
}
int factorial(int num)
{
  if(num == 0 || num == 1)
    return 1;
  return num * factorial(num - 1);
}
int fib(int num)
{
  if(num == 0 || num == 1)
    return 1;
  return fib(num - 1) + fib(num - 2);
}