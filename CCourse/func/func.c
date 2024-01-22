#include <stdio.h>
void show_()
{
  printf("hello");
}
// 函数声明
double power(const double, const int);

int main()
{
  show_();
  double r = power(2,10);
  printf("r = %.2lf \n", r);
  return 0;
}
// 函数实现 函数中是值传递
double power(const double x, const int n){
  double r = x;
  for (int i = 0; i < n; i++)
  {
    r*=x;
  }
  return r;
}