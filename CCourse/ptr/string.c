#include <stdio.h>
int str_len(const char* dest)
{
  int end_idx = 0;
  while(dest[end_idx] != '\0'){
    end_idx ++;
  }
  return end_idx;
}
int str_cat(char* dest,const char* src)
{
  int start_idx = str_len(dest);
  printf("start_idx: %d\n",str_len(dest));
  for (int i = 0; i <= str_len(src); i++)
  {
    printf("*(src+%d)+: %c\n", i, *(src+i));
    dest[start_idx+i] = *(src+i);
  }
  return 0;
}
int main()
{
  // >>>>>>>>>> 字符指针和字符串 >>>>>>>>>>
  // 通常char数据类型指针变量称为字符指针
  char ch = 'A';
  char *p;
  p = &ch;
  printf("p address = %p ;p value =  %c \n",p, *p);
  char str[] = "hello world";
  char *p0 = str;
  char *p1 = "hello world";//字符串常量 后面不能通过指针修改这个常量 *p1='A'; 错误
  char *p2 = "hello world";
  printf("*p0 value =  %c \n",*p0);
  printf("p0 address = %p ;p0 value =  %s \n",p0, p0);
  printf("&p1 %p  p1 address = %p ;p1 value =  %s \n",&p1, p1, p1);
  printf("&p2 %p  p2 address = %p ;p2 value =  %s \n",&p2, p2, p2);


  char dest[100] = "welcome";
  char *src = "hello world hahaha";
  str_cat(dest,src);
  puts(dest);
  return 0;
}