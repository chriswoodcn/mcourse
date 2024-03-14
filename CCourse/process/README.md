## 进程

### 进程和程序的区别

- 程序 编译好的可执行文件
  - 存放在磁盘上的指令和数据的有序集合
  - 程序是静态的，没有任何执行的概念
- 进程 一个独立的可调度的任务
  - 执行一个程序所分配的资源的总称
  - 进程是程序的一次执行过程
  - 进程是动态的，包括创建、调度、执行和消亡

### 进程概念

进程不仅包括程序的指令和数据，而且包括程序计数器的值（PC）、CPU 的所有寄存器值以及存储临时数据的进程堆栈

主要进程标识

- 进程号 PID
- 父进程号 PPID

Linux 中进程包含三个段

- 数据段 存放全局变量、常数以及动态数据分配的数据空间（malloc 函数取得的数据空间）
- 正文段 程序中的代码
- 堆栈段 存放函数的返回地址，函数的参数以及程序中的局部变量

进程分类

- 交互进程
  该类进程有 shell 控制和运行，既可以在前台运行，也可以在后台运行
- 批处理进程
  不属于某个终端，被提交到一个队列中以便顺序的执行
- 守护进程
  该类进程在后台运行，一般在 linux 启动时开始执行，系统结束才结束

进程运行状态

- 运行态 R running or runnable (on run queue)
- 睡眠待态 可中断 S interruptible sleep (waiting for an event to complete)
- 睡眠待态 不可中断 D uninterruptible sleep (usually IO)
- 停止态
  进程被中止 T stopped by job control signal
  跟踪 t stopped by debugger during the tracing
- 进入内存交换 W（从内核 2.6 开始无效）
- 死亡态 X 已终止进程，但在进程向量数组中占有一个 task_stat 结构体 X dead (should never be seen)
- 僵尸态 Z defunct ("zombie") process, terminated but not reaped by its parent

### 进程相关命令

ps -- 显示系统进程
top -- 动态显示系统进程
nice -- 按用户指定优先级运行进程
renice -- 改变正在运行进程的优先级
kill -- 向进程发信号
bg -- bg + 暂停的编号 转向后台运行
fg -- 把后台运行的进程放到前台运行

### 进程相关函数

fork

```c
#include <sys/types.h>
#include <unistd.h>
///成功 子进程返回0 父进程返回子进程PID>0  父进程返回-1出错
pid_t fork(void);
///子进程拷贝父进程的全部数据 父子进程的空间数据独立
///copy-on-write机制 子进程实际进行修改的时候才会去拷贝
```

getpid

```c
#include <sys/types.h>
#include <unistd.h>
///获取当前进程号
pid_t getpid(void);
```

getppid

```c
#include <sys/types.h>
#include <unistd.h>
///获取当前父进程号
pid_t getppid(void);
```

exit

```c
#include <stdlib.h>
/// exit _exit区别
/// exit直接进程终止,清除内存空间，销毁其在内核中的各种数据
/// _exit进行了包装，退出之前加了若干到工序 会先清理IO缓冲
void exit(int status);
void _exit(int status);
```

wait&waitpid

```c
#include <sys/types.h>
#include <sys/wait.h>
///防止僵尸态进程出现
///父进程中回收资源 wait(NULL) 阻塞进程直到子进程结束或者该进程接收到一个信号为止，
///如果没有子进程或子进程已经结束 会立即返回
pid_t wait(int *wstatus);
///功能和wait类似 指定等待某个子进程结束
/// pid<0则是等待任一子进程结束
/// 返回值 结束的子进程的进程号 -1--出错 0--WNOHANG且没有子进程结束时
///options 0阻塞 WNOHANG不阻塞
pid_t waitpid(pid_t pid, int *wstatus, int options);
int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
/* This is the glibc and POSIX interface; see
  NOTES for information on the raw system call. */
```

exec 函数族
在一个进程中启动另一个程序，根据文件名或目录找到可执行文件，用它来取代原调用进程的数据、代码、堆栈段
原调用进程的内容除了进程号全部都被替换，可执行文件可以是二进制文件也可以是linux下的可执行脚本
```c
#include <unistd.h>
extern char **environ;
int execl(const char *path, const char *arg, ...
                       /* (char  *) NULL */);
int execlp(const char *file, const char *arg, ...
                       /* (char  *) NULL */);
int execle(const char *path, const char *arg, ...
                       /*, (char *) NULL, char * const envp[] */);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[],
                       char *const envp[]);
```

### 守护进程创建

## 线程

### 线程和进程的区别

### 线程相关函数

pthread_create
pthread_exit
pthread_join

### 线程的同步和互斥

- 同步 信号量
- 互斥 互斥锁

## 进程间通信

### 无名管道

pipe

### 有名管道

mkfifo

### 信号

kill
raise
alarm
pause
signal

### 共享内存

ftok
shmget
shmat
shmdt
shmctl

### 消息队列

msgget
msgsnd
msgrcv
msgctl

### 信号灯

semget
semctl
semop
