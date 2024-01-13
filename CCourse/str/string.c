#include <stdio.h>

int main()
{
  printf(">>>>>>>>>> 字符数组 >>>>>>>>>>\n");
  char a[7] = {'1','2','3','4','5','6'};
  char b[7] = "123456";
  char c[] = "123456";
  char d[7] = {"123456"};
  printf("a %s \n",a);
  printf("b %s \n",b);
  printf("c %s \n",c);
  printf("d %s \n",c);
}