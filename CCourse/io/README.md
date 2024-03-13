## 标准 IO

### 文件基础

#### 文件分类

- 常规文件 ascii 码文件 二进制文件 -
- 目录 d
- 字符设备 c
- 块设备 b
- 有名管道 p
- 套接字 s
- 符号链接 l

#### UNIX 基础知识-系统调用和库函数

库函数,为实现某个功能封装起来的 API 集合，更加便于应用程序移植，是语言和应用程序的一部分
系统调用,用户空间进程访问内核的接口,提高系统安全性，提高程序可移植性，是操作系统的一部分

### 标准 IO 概念

标准 IO 是 C 库中提供的一组专门用于输入输出的函数
标准 IO 通过缓冲机制减少系统调用次数，提高效率

- 文件指针

FILE 指针：每个被使用的文件都在内存中开辟一个区域，用来存放文件有关信息，这些信息保存在
一个结构体变量中，该结构体类型由系统定义，取名 FILE;
标准 IO 库所有的操作都是围绕 stream 来进行的，流用 FILE\*来描述
标准 IO 库由 Dennis Ritchie 于 1975 年左右编写

- 流
  定义：所以的 IO 操作仅是简单的从程序移进或者移出，这种字节流就称为流
  分类：文本流/二进制流
  标准 IO 默认打开三个流：stdin stdout stderr
- 缓冲区
  全缓存：与文件相关
  刷新缓存区的条件: 1.程序正常退出 2.缓存区满刷新 3.fflush 强制刷新
  行缓存： 与终端相关
  刷新缓存区的条件：1.\n 刷新 2.程序正常退出 3.缓存区满刷新 4.fflush 强制刷新
  不缓存

### 相关函数

fopen -- FILE _fopen(const char _ path, const char * mode);
fclose -- int fclose(FILE *stream);
freopen -- FILE *freopen(const char *pathname, const char *mode, FILE *stream);

> 每次一个字符的读写流

fgetc -- int fgetc(FILE *stream); 成功返回 ascii 码值 失败或结尾返回 EOF
fputc -- int fputc(int c, FILE *stream);

> 每次一行的读写流

fgets -- char *fgets(char *s, int size, FILE *stream); 成功返回 s, 失败或结尾返回 NULL
fputs -- int fputs(const char *s, FILE \*stream);

> 直接 IO（二进制 IO）

fread -- size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
fwrite -- size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
定位流
fseek -- int fseek(FILE *stream, long offset, int whence); offset 正数向结尾 负数向开头
ftell -- long ftell(FILE *stream); 显示当前文件流位置
rewind -- void rewind(FILE \*stream); 相当于 fseek(stream, 0L, SEEK_SET)

## 文件 IO

### 文件 IO 概念

- 基础概念
  文件 IO 是 posix 定义的一组函数
  文件 IO 不带缓冲机制
  通过文件描述符访问（标准 IO 通过文件流访问带缓冲）
- 文件描述符： 非负整数，linux 为每个打开的文件分配一个文件描述符，
  从零开始，依次递增
  0,1,2 对应 标准输出 标准输入 标准错误

### 相关函数

open/creat

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char* pathname, int flags);
int open(const char* pathname, int flags, mode_t mode);
int creat(const char* pathname, int flags, mode_t mode);
///返回的一定是最小可用文件描述符 失败返回-1
///flags O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_TRUNC 清空, O_APPEND 追加
///mode
// 1执行 001
// 2写   010
// 4读   100
// 0600 0777
///实际创建文件的权限 = mode & (~umask）#umask一般为0002也可以修改
```

close

```c
#include <unistd.h>

int close(int fd);
```

read

```c
#include <unistd.h>
///返回实际读取到的字节数 0表示到结尾 -1出错 buf存放地址 count每次读取的字节数
ssize_t read(int fd, void *buf, size_t count);

ssize_t pread(int fd, void *buf, size_t count, off_t offset);
```

write

```c
#include <unistd.h>
///返回实际写的字节数 -1出错 buf数据开始地址 count每次写的字节数
ssize_t write(int fd, const void *buf, size_t count);

ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
```

lseek

```c
#include <sys/types.h>
#include <unistd.h>
///定位一个已经打开的文件 成功返回文件的当前位移 -1出错
off_t lseek(int fd, off_t offset, int whence);
```

### 文件属性函数

stat

```c
#include <sys/stat.h>
///通过路径获取文件信息 0成功 -1失败 buf描述文件有关信息结构体
int stat(const char *restrict path, struct stat *restrict buf);

struct stat {
  dev_t     st_dev;         /* ID of device containing file */
  ino_t     st_ino;         /* Inode number */
  mode_t    st_mode;        /* File type and mode */
  nlink_t   st_nlink;       /* Number of hard links */
  uid_t     st_uid;         /* User ID of owner */
  gid_t     st_gid;         /* Group ID of owner */
  dev_t     st_rdev;        /* Device ID (if special file) */
  off_t     st_size;        /* Total size, in bytes */
  blksize_t st_blksize;     /* Block size for filesystem I/O */
  blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

  /* Since Linux 2.6, the kernel supports nanosecond
    precision for the following timestamp fields.
    For the details before Linux 2.6, see NOTES. */

  struct timespec st_atim;  /* Time of last access */
  struct timespec st_mtim;  /* Time of last modification */
  struct timespec st_ctim;  /* Time of last status change */

#define st_atime st_atim.tv_sec      /* Backward compatibility */
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};
///判断文件类型的宏
stat(pathname, &sb);
if (S_ISREG(sb.st_mode)) {
    /* Handle regular file */
}
S_ISREG(m)  is it a regular file?
S_ISDIR(m)  directory?
S_ISCHR(m)  character device?
S_ISBLK(m)  block device?
S_ISFIFO(m) FIFO (named pipe)?
S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)
S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)
///另一种判断文件类型的方式
stat(pathname, &sb);
if ((sb.st_mode & S_IFMT) == S_IFREG) {
    /* Handle regular file */
}
///文件权限
stat(pathname, &sb);
if (sb.st_mode & S_IRWXU) {
    /* owner has read, write, and execute permission */
}
S_IRWXU     00700   owner has read, write, and execute permission
S_IRUSR     00400   owner has read permission
S_IWUSR     00200   owner has write permission
S_IXUSR     00100   owner has execute permission

S_IRWXG     00070   group has read, write, and execute permission
S_IRGRP     00040   group has read permission
S_IWGRP     00020   group has write permission
S_IXGRP     00010   group has execute permission

S_IRWXO     00007   others  (not  in group) have read, write, and execute permission
S_IROTH     00004   others have read permission
S_IWOTH     00002   others have write permission
S_IXOTH     00001   others have execute permission
```

lstat

```c
/// 路径如果是链接文件返回链接文件本身描述不会返回链接指向的文件描述 0成功 -1失败
int lstat(const char *restrict path, struct stat *restrict buf);
```

fstat

```c
///通过fd获取文件信息 0成功 -1失败
int fstat(int fildes, struct stat *buf);
```

opendir

```c
#include <sys/types.h>
#include <dirent.h>
///打开目录 成功返回目录流指针
DIR *opendir(const char *name);
```

closedir

```c
#include <sys/types.h>
#include <dirent.h>
///关闭目录
int closedir(DIR *dirp);
```

readdir

```c
#include <dirent.h>
///读取目录
struct dirent *readdir(DIR *dirp);

struct dirent {
    ino_t          d_ino;       /* Inode number */
    off_t          d_off;       /* Not an offset; see below */
    unsigned short d_reclen;    /* Length of this record */
    unsigned char  d_type;      /* Type of file; not supported
                                  by all filesystem types */
    char           d_name[256]; /* Null-terminated filename */
};
// d_type
// DT_BLK      This is a block device.
// DT_CHR      This is a character device.
// DT_DIR      This is a directory.
// DT_FIFO     This is a named pipe (FIFO).
// DT_LNK      This is a symbolic link.
// DT_REG      This is a regular file.
// DT_SOCK     This is a UNIX domain socket.
// DT_UNKNOWN  The file type could not be determined.
```

### 库的制作

库： 可执行程序的二进制代码形式，可以被操作系统载入内存执行

> 静态库和动态库不同点在于代码被载入的时刻不同

### 静态库

程序编译时会被链接到目标代码中，程序运行时不再需要，体积较大

#### 创建静态库

- ar 命令创建
  gcc -c myhello.c -o myhello.o
  ar crs libmyhello.a myhello.o 命名规范是以 lib 为前缀，紧接着跟静态库名，扩展名为.a

- 使用静态库
  库名：lib（name）.a
  gcc -o hello main.c -L. -lmyhello

### 动态库

在程序编译时不会被链接到目标代码中，而是在程序运行时载入，因此在程序运行时还需要动态库存在

- 创建共享库
  gcc -fPIC -Wall -c hello.c              #-fPIC 创建与地址无关的编译程序
  gcc -shared -o libmyhello.so hello.o
  gcc -o main main.c -L. -lmyhello

> 动态库路径问题 
> 1.库拷贝到/usr/lib 或者/lib 目录下 
> 2.LD_LIBRARY_PATH环境变量中加上库所在路径
> 3.添加/etc/ld.so.conf.d/*.conf文件 把库所在路径加到文件末尾 执行ldconfig刷新
