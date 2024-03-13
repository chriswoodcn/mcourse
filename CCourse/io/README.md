## 标准IO
### 文件基础
#### 文件分类
- 常规文件 ascii码文件 二进制文件 -
- 目录 d
- 字符设备 c
- 块设备 b
- 有名管道 p
- 套接字 s
- 符号链接 l
#### UNIX基础知识-系统调用和库函数
库函数,为实现某个功能封装起来的API集合，更加便于应用程序移植，是语言和应用程序的一部分
系统调用,用户空间进程访问内核的接口,提高系统安全性，提高程序可移植性，是操作系统的一部分
### 标准IO概念
标准IO是C库中提供的一组专门用于输入输出的函数
标准IO通过缓冲机制减少系统调用次数，提高效率
- 文件指针 

FILE指针：每个被使用的文件都在内存中开辟一个区域，用来存放文件有关信息，这些信息保存在
一个结构体变量中，该结构体类型由系统定义，取名FILE;
标准IO库所有的操作都是围绕stream来进行的，流用FILE*来描述
标准IO库由Dennis Ritchie于1975年左右编写
- 流
定义：所以的IO操作仅是简单的从程序移进或者移出，这种字节流就称为流
分类：文本流/二进制流
标准IO默认打开三个流：stdin stdout stderr
- 缓冲区
 全缓存：与文件相关
  刷新缓存区的条件: 1.程序正常退出 2.缓存区满刷新 3.fflush强制刷新
 行缓存： 与终端相关
  刷新缓存区的条件：1.\n刷新 2.程序正常退出 3.缓存区满刷新 4.fflush强制刷新
 不缓存
### 相关函数
fopen -- FILE *fopen(const char * path, const char * mode);
fclose -- int fclose(FILE *stream);
freopen -- FILE *freopen(const char *pathname, const char *mode, FILE *stream);
>每次一个字符的读写流

fgetc -- int fgetc(FILE *stream); 成功返回ascii码值 失败或结尾返回EOF
fputc -- int fputc(int c, FILE *stream);
>每次一行的读写流

fgets -- char *fgets(char *s, int size, FILE *stream); 成功返回s, 失败或结尾返回NULL
fputs -- int fputs(const char *s, FILE *stream);
>直接IO（二进制IO）

fread -- size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
fwrite -- size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

## 文件IO
### 文件IO概念
文件描述符
### 相关函数
open
close
read
write
lseek
### 文件属性函数
stat 
lstat
fstat
opendir
closedir
readdir
### 库的制作
静态库
动态库