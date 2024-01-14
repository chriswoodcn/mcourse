#include <stdio.h>

int main()
{
  printf(">>>>>>>>>> 字符数组 >>>>>>>>>>\n");
  char a[7] = {'1','2','3','4','5','6'};
  char b[7] = "123456";
  char c[] = "123456";
  char d[7] = {"123456"};
  printf(a);
  printf("\n");
  printf(c);
  printf("\n");
  printf("a %s \n",a); //%s 打印必须是字符串 即字符数组最后又\0
  printf("b %s \n",b);
  printf("c %s \n",c);
  printf("d %s \n",c);
  //字符串 字符数组带有\0结束标志
  char fruit[][10] = {"banana","apple","watermelen","pear"};
  int n = sizeof(fruit) / sizeof(fruit[0]); // 行数
  int m = sizeof(fruit[0]) / sizeof(char);
  printf("fruit row = %d \n",n);
  printf("fruit col = %d \n",m);
  for (size_t i = 0; i < n; i++)
  {
    printf("%s \n",fruit[i]);
  }

  return 0;
}