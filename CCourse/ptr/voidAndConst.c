#include <stdio.h>

void void_test()
{
    // >>>>>>>>>> void指针 >>>>>>>>>>
    void* void_p;
    int a = 10;
    double b = 3.14;
    void_p = (void*)&a;
    printf("*void_p %d \n",*(int*)void_p);
    void_p = (void*)&b;
    printf("*void_p %.2lf \n",*(double*)void_p);
}
void const_test()
{
  const int a = 100;
  printf("a = %d \n",a);
  // a = 200;
  int* p = &a;
  *p = 200;
  printf("a = %d \n",a);
  printf("*p = %d \n",*p);
  // >>>>>>>>>> const修饰指针 >>>>>>>>>>
  const int b = 100;
  const int* p0; //const放*前面 *p的值 readonly
  int* const p0; //const放*后面 p的值readonly
  // p0 = &b;
  // (*p)++;
  // p0 = &a;
}
int main(int argc, const char* argv[])
{
  void_test();
  const_test();
  return 0;
}