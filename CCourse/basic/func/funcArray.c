#include <stdio.h>

int array_sum(int arr[],int size)
{
  printf("arr size = %d\n", sizeof(arr)); //这里sizeof计算的是int* 不是int[]
  int res = 0;
  for (int i = 0; i < size; i++)
  {
    res += *(arr+i);
  }
  return res;
}
char* delete_space(char s[],int size)
{
  char* p = s;
  char s2[size];
  int i = 0;
  while (*p!='\0')
  {
    if(*p == ' '){
      p++;
      continue;
    }
    s2[i] = *p;
    p++;
    i++;
  }
  s2[i] = '\0';
  return s2;
}
int main()
{
  // >>>>>>>>>> 函数中数组传参 >>>>>>>>>>
  // 数组传参需要传递数组的 起始地址值 和 数据长度
  int a[] = {1,2,3,4,5,6,7,8,9};
  int r = array_sum(a, sizeof(a)/sizeof(int));
  printf("array_sum r = %d \n",r);
  char s[] = " hello world ";
  printf("s = %s \n", s);
  char* s2 = delete_space(s, 14);
  printf("s2 = %s \n", s2);
  return 0;
}