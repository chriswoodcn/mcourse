## 进程
### 进程和程序的区别
### 进程概念
### 进程相关命令
ps top 
nice 
renice
kill 
bg 
fg 
jobs
fork 
getpid 
getppid 
exec族
### 进程相关函数
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