#include <stdio.h>

int main()
{
  // >>>>>>>>>> 指针数组 >>>>>>>>>>
  int a[] = {1,2,3,4,5,6};
  int *p[10] = {NULL}; 
  p[0] = a;
  p[1] = a + 1;
  for (int i = 0; i < sizeof(p)/sizeof(int*); i++)
  {
    printf("p[%d] = %p \n", i , p[i]);
  }
  

  printf("p[0] = %d \n", *(p[0]));
  printf("p[1] = %d \n", *(p[0]+1));
  return 0;
}