#include <stdio.h>

int main()
{
  printf(">>>>>>>>>> 打印杨辉三角 >>>>>>>>>>\n");
  int a[10][10] = {{1}};
  for (int i = 0; i < 10; i++)
  {
    a[i][0] = 1;
    for (int j = 1; j <= i; j++)
    {
      a[i][j] = a[i-1][j-1] + a[i-1][j];
    }
  }
    
  for (size_t i = 0; i < 10; i++)
  {
    for (size_t j = 0; j <= i; j++)
    {
      printf("%-4d",a[i][j]);
    }
    putchar('\n');
  }
  
}