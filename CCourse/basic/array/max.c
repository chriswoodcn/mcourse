#include <stdio.h>

void getMax();

int main()
{
  printf(">>>>>>>>>> 数组最大值 >>>>>>>>>>\n");
  getMax();
}
void getMax()
{
  int a[3][4] = {
    {15,64,22,54},
    {1,12,14,84},
    {0,3,8,65}
  };
  int max = 0;
  int row = 0;
  int col = 0;
  for (size_t i = 0; i < 3; i++)
  {
    for (size_t j = 0; j < 4; j++)
    {
      printf("%-3d",a[i][j]);
      if(a[i][j] > max)
      {
        max = a[i][j];
        row = i;
        col = j;
      }
    }
    putchar('\n');
  }
  printf("maxValue:%d row:%d col:%d\n",max,row,col);
}