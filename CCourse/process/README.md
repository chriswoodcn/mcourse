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
原调用进程的内容除了进程号全部都被替换，可执行文件可以是二进制文件也可以是 linux 下的可执行脚本

```c
#include <unistd.h>
extern char **environ;

// execl("/bin/ls","ls","-l",NULL); 以列表形式列出参数 NULL终止
int execl(const char *path, const char *arg, ...
                       /* (char  *) NULL */);
// 多一个环境变量
int execle(const char *path, const char *arg, ...
                       /*, (char *) NULL, char * const envp[] */);
// execlp("ls","ls","-l",NULL); 只需要指定名字，不需要路径
int execlp(const char *file, const char *arg, ...
                       /* (char  *) NULL */);
// char* arg[] = {"ls","-l",NULL};
// execv("/bin/ls", arg); 以数组指针传参
int execv(const char *path, char *const argv[]);
// execvp("ls",arg); 只需要指定名字，不需要路径
int execvp(const char *file, char *const argv[]);
// 多一个环境变量
// char* arg[] = {"env",NULL};
// char* envp = {"PATH=hello",NULL};
// execvpe("env",arg,envp);
int execvpe(const char *file, char *const argv[],
                       char *const envp[]);
```

### 守护进程创建

守护进程也就是 Daemon 进程 linux 中的后台服务进程，独立于控制终端并周期的执行某种任务或等待处理某些发生的事件
通常在系统启动时开始运行，系统关闭时终止
linux 中大多数服务是用守护进程实现的
ps aux ？是守护进程

- 守护进程编写步骤
  - 创建子进程，父进程退出
    子进程被 1 进程接管，变后台进程
  - 在子进程中创建新会话
    让子进程成为会话组组长
  - 改变当前目录为根目录
    增加可移植性
  - 重设文件权限掩码
    增加文件操作权限
  - 关闭文件描述符
    关掉不相关的文件

```c
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
  pid_t pid;
  if((pid = fork())<0){
    perror("fork error");
    return -1;
  }
  else if(pid==0){
    /// 用于创建一个新的会话 并使当前进程成为新会话组组长 脱离所有其他进程的控制
    pid_t sid = setsid();
    /// 让传入的目录成为当前进程的工作目录
    chdir("/");
    /// 重设权限掩码 0权限最大
    umask(0);
    /// getdtablesize获取文件描述符个数
    int i;
    for(i =0; i < getdtablesize();++i){
      close(i);
    }
    // 开始守护进程中的逻辑
    int fd = open("/tmp/demo_daemon_process.log", O_WRONLY|O_CREAT|O_APPEND, 0777);
    time_t t;
    struct tm *tm;
    while(1){
      time(&t);
      tm = localtime(&t);
      char* str[20]={0};
      sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d\n", tm->tm_year + 1900,
           tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec)
      write(fd, str, 20);
      sleep(1);
    }
    close(fd);
  }
  else{
    _exit(0);
  }
  return 0;
}
```

## 线程

- 概念
  每个用户进程有自己的地址空间 系统为每个用户进程创建一个 task_struct 描述进程
  task_struct 和地址空间映射表一起用来表示一个进程
  因进程地址空间私有，进程间上下文切换系统开销较大，许多系统引入了轻量级进程概念--线程
  在同一个进程中创建的线程共享该进程的地址空间 linux 里同样用 task_struct 描述一个线程，线程进程都参与统筹
- 特点
  通常线程指共享相同地址空间的多个任务
- 优点
  提高任务切换的效率，多线程通信简单
- 线程和进程的区别

- 进程中多个线程共享的资源
  - 可执行指令
  - 静态数据
  - 进程中打开的文件描述符
  - 信号处理函数
  - 当前工作目录
  - 用户 ID
  - 用户组 ID
- 线程私有资源
  - TID
  - PC 程序计数器和相关寄存器
  - 堆栈 局部变量和返回地址
  - 错误号 errno
  - 信号掩码和优先级
  - 执行状态和属性

### 线程和进程的区别

### 线程相关函数

NPTL 线程库

pthread_create

```c
#include <pthread.h>
/// void *(*start_routine) (void *) 函数指针
/// -lpthread 编译时需要去链接库
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                  void *(*start_routine) (void *), void *arg);
///取消线程
void pthread_cancel(pthread_t thread);
```

pthread_exit

```c
#include <pthread.h>
///线程退出
void pthread_exit(void *retval);
```

pthread_join

```c
#include <pthread.h>
/// 阻塞主线程 *retval指向线程返回的参数
int pthread_join(pthread_t thread, void **retval);
```

### 线程的同步和互斥

- 同步 信号量
  信号量代表某一类资源，值表示系统中该资源的数量
  信号量是一个受保护的变量，只能通过三种方式访问 1.初始化 2.P 操作(申请资源) 3.V 操作(释放资源)
  信号量的值是非负整数

```c
// pthread库常用信号量操作函数
#include <semaphore.h>
/// 初始化操作 pshared 0线程间操作 非0进程间使用 value初始化信号量
int sem_init(sem_t *sem, int pshared, unsigned int value);
/// P操作 申请资源 信号量-1 初始化信号量为0时会阻塞等待信号量
int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem);
int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
/// V操作 释放资源 信号量+1
int sem_post(sem_t *sem);
int sem_getvalue(sem_t *sem, int *sval);
```

- 互斥 互斥锁
  保证共享数据操作的完整性
  主要用来保护临界资源，任何时刻最多只能有一个线程能访问该资源

```c
#include <pthread.h>
/// 以动态方式创建互斥锁的，参数attr指定了新建互斥锁的属性  成功执行后，互斥锁被初始化为未锁住态
int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
/// 使用宏静态方式创建互斥锁
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;（一个结构常量）
/// 注销互斥锁
int pthread_mutex_destroy(pthread_mutex_t *mutex);
/// 加锁
int pthread_mutex_lock(pthread_mutex_t *mutex);
/// 解锁
int pthread_mutex_unlock(pthread_mutex_t *mutex);
/// 锁已经被占据时返回EBUSY而不是挂起等待
int pthread_mutex_trylock(pthread_mutex_t *mutex);
```

```c
/* mutex.c */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* 全局变量 */
int gnum = 0;
/* 互斥量 */
pthread_mutex_t mutex;

/* 声明线程运行服务程序. */
static void pthread_func_1(void);
static void pthread_func_2(void);

int main (void)
{
 /*线程的标识符*/
  pthread_t pt_1 = 0;
  pthread_t pt_2 = 0;
  int ret = 0;

  /* 互斥初始化. */
  pthread_mutex_init(&mutex, NULL);
  /*分别创建线程1、2*/
  ret = pthread_create(&pt_1,  //线程标识符指针
                       NULL,  //默认属性
                       (void*)pthread_func_1, //运行函数
                       NULL); //无参数
  if (ret != 0)
  {
     perror("pthread_1_create");
  }

  ret = pthread_create(&pt_2, //线程标识符指针
                       NULL,  //默认属性
                       (void *)pthread_func_2, //运行函数
                       NULL); //无参数
  if (ret != 0)
  {
     perror("pthread_2_create");
  }
  /*等待线程1、2的结束*/
  pthread_join(pt_1, NULL);
  pthread_join(pt_2, NULL);

  printf("main programme exit!/n");
  return 0;
}

/*线程1的服务程序*/
static void pthread_func_1(void)
{
  int i = 0;

  for (i=0; i<3; i++) {
    printf("This is pthread_1!/n");
    pthread_mutex_lock(&mutex); /* 获取互斥锁 */
    /* 注意，这里以防线程的抢占，造成一个线程在另一个线程sleep时多次访问互斥资源，所以sleep要在得到互斥锁后调用. */
    sleep(1);
    /*临界资源*/
    gnum++;
    printf("Thread_1 add one to num:%d/n", gnum);
    pthread_mutex_unlock(&mutex); /* 释放互斥锁. */
  }

  pthread_exit(NULL);
}

/*线程2的服务程序*/
static void pthread_func_2(void)
{
  int i = 0;

  for (i=0; i<5; i++)  {
    printf ("This is pthread_2!/n");
    pthread_mutex_lock(&mutex); /* 获取互斥锁. */
    /* 注意，这里以防线程的抢占，造成一个线程在另一个线程sleep时多次访问互斥资源，所以sleep要在得到互斥锁后调用. */
    sleep(1);
    /* 临界资源. */
    gnum++;
    printf("Thread_2 add one to num:%d/n",gnum);
    pthread_mutex_unlock(&mutex); /* 释放互斥锁. */
  }

  pthread_exit(NULL);
}

```

- 条件变量
  一般搭配互斥锁使用，实现同步机制

```c
/// 初始化条件变量 0--成功 非0--失败
int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
/// 无条件等待信号的产生  0--成功 非0--失败  cond要等待的条件 mutex对应锁
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *mutex);
/// 给条件变量发送信号 0--成功 非0--失败
int pthread_cond_signal(pthread_cond_t *restrict cond);
/// 将条件变量销毁 0--成功 非0--失败
int pthread_cond_destroy(pthread_cond_t *restrict cond);
```

```c
/* mutex.c */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* 全局变量 */
int gnum = 0;
/* 互斥量 */
pthread_mutex_t mutex;
/* 条件变量 */
pthread_cond_t cond;

/* 声明线程运行服务程序. */
static void pthread_func_1(void);
static void pthread_func_2(void);

int main (void)
{
 /*线程的标识符*/
  pthread_t pt_1 = 0;
  pthread_t pt_2 = 0;
  int ret = 0;

  /* 互斥初始化. */
  pthread_mutex_init(&mutex, NULL);
  /* 条件变量初始化. */
  ret = pthread_cond_init(&cond, NULL);
  if (ret < 0)
  {
     perror("pthread_cond_init error");
     return -1;
  }

  /*分别创建线程1、2*/
  ret = pthread_create(&pt_1,  //线程标识符指针
                       NULL,  //默认属性
                       (void*)pthread_func_1, //运行函数
                       NULL); //无参数
  if (ret != 0)
  {
     perror("pthread_1_create");
  }

  ret = pthread_create(&pt_2, //线程标识符指针
                       NULL,  //默认属性
                       (void *)pthread_func_2, //运行函数
                       NULL); //无参数
  if (ret != 0)
  {
     perror("pthread_2_create");
  }
  /*等待线程1、2的结束*/
  pthread_join(pt_1, NULL);
  pthread_join(pt_2, NULL);
  /*销毁条件变量*/
  pthread_cond_destroy(&cond);

  printf("main programme exit!/n");
  return 0;
}

/*线程1的服务程序*/
static void pthread_func_1(void)
{
  int i = 0;

  for (i=0; i<3; i++) {
    sleep(1); //先让线程2竞争到锁等待条件产生
    printf("This is pthread_1!/n");
    pthread_mutex_lock(&mutex); /* 获取互斥锁 */
    /* 注意，这里以防线程的抢占，造成一个线程在另一个线程sleep时多次访问互斥资源，所以sleep要在得到互斥锁后调用. */
    sleep(1);
    /*临界资源*/
    gnum++;
    printf("Thread_1 add one to num:%d/n", gnum);
    // 给条件变量发送信号
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex); /* 释放互斥锁. */
  }

  pthread_exit(NULL);
}

/*线程2的服务程序*/
static void pthread_func_2(void)
{
  int i = 0;

  for (i=0; i<5; i++)  {
    printf ("This is pthread_2!/n");
    pthread_mutex_lock(&mutex); /* 获取互斥锁. */
    //等待条件产生
    pthread_cond_wait(&cond, &mutex);
    /* 注意，这里以防线程的抢占，造成一个线程在另一个线程sleep时多次访问互斥资源，所以sleep要在得到互斥锁后调用. */
    sleep(1);
    /* 临界资源. */
    gnum++;
    printf("Thread_2 add one to num:%d/n",gnum);
    pthread_mutex_unlock(&mutex); /* 释放互斥锁. */
  }

  pthread_exit(NULL);
}
```

## 进程间通信

### 传统进程间通讯方式

#### 无名管道

内核空间创建管道
特点：只能用于具有亲缘关系的进程间通信；半双工通信模式，固定的读和写端；管道看作特殊的文件，可以使用文件 IO 的 read 和 write

pipe

```c
#include <unistd.h>
/// 0创建成功  fd[0]读   fd[1]写
/// 当管道没有数据  读操作阻塞
/// 管道装满数据 4k 继续写，管道缓冲区一有空闲区域，写进程就会试图写入，读进程一直不读走数据，写操作一直阻塞
/// 读端关闭 写数据无意义 管道破裂 内核传来SIGPIPE信号
int pipe(int pipefd[2]);
```

#### 有名管道

mkfifo

```c
#include <sys/types.h>
#include <sys/stat.h>
/// 创建FIFO文件
int mkfifo(const char *pathname, mode_t mode);
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(){
  int fd;
  char buf[64] = {0};
  if(mkfifo("./fifo",0666)<0){
    if(errno == EEXIST){ /* 注意此处已存在fifo情况的判断 */
      printf("fifo exist\n");
    }else{
      perror("mkfifo error");
      return -1;
    }
  }else{
    fd = open("./fifo", O_RDWR);
    // 读写逻辑
  }
}
```

#### 信号

信号的生存周期：

- 内核进程 信号产生
- 用户进程 信号注册-信号注销-信号处理
  用户进程对信号的响应方式
  忽略信号 不做处理 有两个信号不能忽略 SIGKILL SIGSTOP
  捕捉信号 定义信号处理函数，当信号发生执行对应处理函数
  执行缺省操作 linux 每种信号的默认操作

信号

```txt
1) SIGHUP       2) SIGINT       3) SIGQUIT      4) SIGILL       5) SIGTRAP
6) SIGABRT      7) SIGBUS       8) SIGFPE       9) SIGKILL     10) SIGUSR1
11) SIGSEGV     12) SIGUSR2     13) SIGPIPE     14) SIGALRM     15) SIGTERM
16) SIGSTKFLT   17) SIGCHLD     18) SIGCONT     19) SIGSTOP     20) SIGTSTP
21) SIGTTIN     22) SIGTTOU     23) SIGURG      24) SIGXCPU     25) SIGXFSZ
26) SIGVTALRM   27) SIGPROF     28) SIGWINCH    29) SIGIO       30) SIGPWR
31) SIGSYS      34) SIGRTMIN    35) SIGRTMIN+1  36) SIGRTMIN+2  37) SIGRTMIN+3
38) SIGRTMIN+4  39) SIGRTMIN+5  40) SIGRTMIN+6  41) SIGRTMIN+7  42) SIGRTMIN+8
43) SIGRTMIN+9  44) SIGRTMIN+10 45) SIGRTMIN+11 46) SIGRTMIN+12 47) SIGRTMIN+13
48) SIGRTMIN+14 49) SIGRTMIN+15 50) SIGRTMAX-14 51) SIGRTMAX-13 52) SIGRTMAX-12
53) SIGRTMAX-11 54) SIGRTMAX-10 55) SIGRTMAX-9  56) SIGRTMAX-8  57) SIGRTMAX-7
58) SIGRTMAX-6  59) SIGRTMAX-5  60) SIGRTMAX-4  61) SIGRTMAX-3  62) SIGRTMAX-2
63) SIGRTMAX-1  64) SIGRTMAX
```

kill

```c
#include <sys/types.h>
#include <signal.h>
/// 向任意进程发送任意信号
/// pid = 0 发送到调用的进程组中的每个进程
/// pid = -1 发送到调用的进程组中的每个进程 1除外
/// sig = 0  用于检查是否存在进程ID或进程组ID允许呼叫者发出信号
int kill(pid_t pid, int sig);
```

raise

```c
#include <signal.h>
///给自己发信号
int raise(int sig);
```

alarm

```c
#include <unistd.h>
/// seconds之后内核进程向当前进程发送SIGALRM信号
unsigned int alarm(unsigned int seconds);
```

pause

```c
#include <unistd.h>
/// 当前进程或线程睡眠 直到有信号过来或者终止进程或线程
int pause(void);
```

signal

```c
#include <signal.h>

typedef void (*sighandler_t)(int);
/// ANSI C signal handling 信号处理函数
/// sighandler_t=SIG_IGN 忽略
/// sighandler_t=SIG_DFL 默认
/// 返回上一个处理函数
sighandler_t signal(int signum, sighandler_t handler);
```

### IPC 对象

#### 共享内存

共享内存是进程间通讯效率最高的，进程直接读写内存不需要拷贝
由于多个进程共享一段内存，因此也需要依靠某种同步机制，如互斥锁和信号量

##### 共享内存使用步骤

- 创建、打开共享内存
- 映射共享内存
- 撤销共享内存映射
- 删除共享内存映射

ftok

```c
#include <sys/types.h>
#include <sys/ipc.h>
/// 产生KEY值
key_t ftok(const char *pathname, int proj_id);
```

shmget

```c
#include <sys/ipc.h>
#include <sys/shm.h>
/// 打开共享内存 size-共享内存字节大小 shmflg-同open函数权限，也可用八进制表示法
/// 成功返回共享内存段标识符
/// shmflg IPC_CREAT 创建一个新段。如果不使用该标志，则将找到与key关联的段并检查用户是否有访问该段的权限
/// shmflg IPC_EXCL 与IPC_CREAT一起使用以确保该调用创建段。如果该段已经存在，则失败
int shmget(key_t key, size_t size, int shmflg);
```

shmat/shmdt/shmctl

```c
#include <sys/types.h>
#include <sys/shm.h>
/// shmaddr将共享内存映射到指定地址 NULL表示系统自动完成映射
/// shmflg SHM_RDONLY 共享内存只读 默认0 可读写
/// 成功返回映射后地址 出错-1
void *shmat(int shmid, const void *shmaddr, int shmflg);
/// 取消映射
/// 成功返回0 出错-1
int shmdt(const void *shmaddr);
/// 删除或设置共享内存
/// cmd IPC_STAT IPC_SET IPC_RMID IPC_INFO 
///     SHM_INFO SHM_STAT SHM_STAT_ANY SHM_LOCK SHM_UNLOCK
// struct shmid_ds {
//     struct ipc_perm shm_perm;    /* Ownership and permissions */
//     size_t          shm_segsz;   /* Size of segment (bytes) */
//     time_t          shm_atime;   /* Last attach time */
//     time_t          shm_dtime;   /* Last detach time */
//     time_t          shm_ctime;   /* Last change time */
//     pid_t           shm_cpid;    /* PID of creator */
//     pid_t           shm_lpid;    /* PID of last shmat(2)/shmdt(2) */
//     shmatt_t        shm_nattch;  /* No. of current attaches */
//     ...
// };
// struct ipc_perm {
//     key_t          __key;    /* Key supplied to shmget(2) */
//     uid_t          uid;      /* Effective UID of owner */
//     gid_t          gid;      /* Effective GID of owner */
//     uid_t          cuid;     /* Effective UID of creator */
//     gid_t          cgid;     /* Effective GID of creator */
//     unsigned short mode;     /* Permissions + SHM_DEST and
//                                 SHM_LOCKED flags */
//     unsigned short __seq;    /* Sequence number */
// };
int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```

#### 消息队列

msgget
msgsnd
msgrcv
msgctl

#### 信号灯

semget
semctl
semop

### BSD

scoket
