#include <string.h>
#include <stdio.h>
#include <ctype.h>

int main()
{
  // >>>>>>>>>> 字符串长度 strlen 不包含\0 >>>>>>>>>>
  char s[] = "\tma\nke\\\x69\141";
  printf("strlen: %d \n",strlen(s));
  printf("strlen: %d \n",sizeof(s)/sizeof(char));
  // >>>>>>>>>> 字符串拷贝 strcpy >>>>>>>>>>
  char src[] = "welcome";
  char dest1[10];
  //返回数组1的首地址
  strcpy(dest1,src);  // 注意：数组1需要足够大 拷贝时\0一样拷贝
  printf("dest1: %s\n",dest1);
  char dest2[20]="aaaaaaaaaa";
  strncpy(dest2,src,4);
  printf("dest2: %s\n",dest2);
  // >>>>>>>>>> 字符串连接 strcat >>>>>>>>>>
  char* cat = strncat(dest2, src, 5);
  printf("cat: %s\n",cat);
  printf("dest2: %s\n",dest2);
  // >>>>>>>>>> 字符串比较 strcmp >>>>>>>>>>
  char str1[] = "quit";
  char str2[] = "quit\n";
  int res1 = strcmp(str1,str2);
  int res2 = strncmp(str1,str2,3);
  printf("strcmp res1: %d\n",res1);
  printf("strcmp res2: %d\n",res2);
  // >>>>>>>>>> 字符串查找指定字符 strchr(s,c) >>>>>>>>>>
  // >>>>>>>>>> 字符串查找指定字符（反向） strrchr(s,c) >>>>>>>>>>
  // >>>>>>>>>> 字符串查找指定字符串 strstr(s,s) >>>>>>>>>>

  // >>>>>>>>>> 是否是字符字符 isalpha(c) >>>>>>>>>>
  // >>>>>>>>>> 是否大写字母字符 isupper(c) >>>>>>>>>>
  // >>>>>>>>>> 是否小写字母字符 islower(c) >>>>>>>>>>
  // >>>>>>>>>> 转大写 toupper(c) >>>>>>>>>>
  // >>>>>>>>>> 转小写 tolower(c) >>>>>>>>>>
  // >>>>>>>>>> 是否数字 isdigit(c) >>>>>>>>>>
  return 0;
}