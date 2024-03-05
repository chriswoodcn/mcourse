#include <stdio.h>

int main()
{
  // >>>>>>>>>> 多级指针 >>>>>>>>>>
  int a = 10;
  int *p = &a;
  int ** mp = &p;
  printf("mp %p\n",mp);
  printf("p %p\n",p);
  printf("*p %d **p %d \n",*p , **mp);

  char * s[] = {"apple","pear","potato"};
  int i = 0;
  int n = sizeof(s)/sizeof(char*);
  char **pp = s;
  while (i<n)
  {
    printf("%s %s %s\n",s[i], *(s+i), *(pp+i));
    i++;
  }
  return 0;
}