#include <stdio.h>
#include <string.h>

#define N 10
int reverse1(){
  char arr[N] = {0};
  int n,i;
  printf("please input a string:");
  gets(arr);
  n = strlen(arr);
  for (i = n - 1; i >= 0; i--)
  {
    putchar(arr[i]);
  }
  putchar('\n');
}

int main()
{
  printf(">>>>>>>>>> 输入一个字符串,将其逆序输出 >>>>>>>>>>\n");
  //  scanf gets
  reverse1();
  return 0;
}