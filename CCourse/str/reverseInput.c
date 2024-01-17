#include <stdio.h>
#include <string.h>

#define N 10
void reverse1(){
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

void reverse2(){
  char arr[N] = {0};  
  int n,i,j;
  printf("please input a string:");
  gets(arr);
  n = strlen(arr);
  i = 0;
  j = n - 1;
  char temp;
  while (i != j)
  {
    temp = arr[i];
    arr[j] = arr[i];
    arr[i] = temp;
    i++;
    j--;
  }
  puts(arr);
}
int main()
{
  printf(">>>>>>>>>> 输入一个字符串,将其逆序输出 >>>>>>>>>>\n");
  //  scanf gets
  reverse1();
  return 0;
}