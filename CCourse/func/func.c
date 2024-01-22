#include <stdio.h>
#include <ctype.h>

void show_()
{
  printf("hello");
}
// 函数声明
double power(const double, const int);
void swap(int* a,int* b);
void str_fun();

int main()
{
  show_();
  double r = power(2,10);
  printf("r = %.2lf \n", r);
  int a = 10;
  int b = 20;
  printf("a = %d b = %d \n", a, b);
  swap(&a,&b);
  printf("a = %d b = %d \n", a, b);

  str_fun();
  return 0;
}
// 函数实现 函数中是值传递
double power(const double x, const int n)
{
  double r = x;
  for (int i = 0; i < n; i++)
  {
    r*=x;
  }
  return r;
}
// 传递指针
void swap(int* a,int* b)
{
  int t = *a;
  *a = *b;
  *b = t;
}
int compute_lower_num(char* s,int size)
{
  int i = 0,n = 0;
  while(i<size)
  {
    printf("%c \n",*(s+i));
    if(*(s+i) <= 'Z' && *(s+i) >= 'A'){
      n++;
    }
    i++;
  }
  return n;
}
void to_lower(char* s)
{
  char* p = s;
  while (*p != '\0')
  {
    if(*p <= 'Z' && *p >= 'A'){
      *p += 32;
    }
    p++;
  }
}
void str_fun()
{
  char s[] = "Welcome to ChangZhou";
  int num = compute_lower_num(s,sizeof(s)/sizeof(char));
  printf("upper num = %d\n", num);
  to_lower(s);
  printf("format all to lower : %s\n", s);
}
