#include <stdio.h>
#include <string.h>
//3 使用指针传递地址
char* getstring(char*);
//1 全局变量 char str[20];

int main()
{
  char *r;
  printf("r = %s \n",getstring(r));
  return 0;
}

char* getstring(char* str)
{
  //2 静态变量 static str[20];
  //4 字符串常量的地址
  strcpy(str,"hello");
  return str;
}