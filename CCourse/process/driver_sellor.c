#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
typedef void (*sighandler_t)(int);

pid_t pid, ppid;
// sellor
// 捕捉 SIGINT SIGQUIT SIGUSR1
// 忽略 SIGTSTP
void sellor_sig_handler(int sig) {
  if (sig == SIGINT) {
    if (ppid > 0)
      kill(ppid, SIGUSR1);
    return
  }
  if (sig == SIGQUIT) {
    if (ppid > 0)
      kill(ppid, SIGUSR2);
    return
  }
  if (sig == SIGUSR1) {
    printf("please get off the bus\n");
    _exit(0);
    return
  }
}
// dirver
// 捕捉 SIGUSR1 SIGUSR2 SIGTSTP
// 忽略 SIGINT SIGQUIT
void driver_sig_handler(int sig) {
  if (sig == SIGUSR1) {
    printf("lets gogogo\n");
    return
  }
  if (sig == SIGUSR2) {
    printf("stop the bus\n");
    return
  }
  if (sig == SIGTSTP) {
    kill(pid, SIGUSR1);
    return
  }
}
int main() {
  if ((pid = fork()) < 0) {
    perror("fork error");
    return -1;
  } else if (pid == 0) {
    printf("this is sellor\n");
    pid_t ppid = getppid(); // 获取父进程pid
    signal(int SIGINT, sellor_sig_handler);
    signal(int SIGQUIT, sellor_sig_handler);
    signal(int SIGUSR1, sellor_sig_handler);
    signal(int SIGINT, SIGTSTP);
    while (1) {
    }
  } else {
    printf("this is driver\n");
    // 捕捉
    signal(int SIGUSR1, driver_sig_handler);
    signal(int SIGUSR2, driver_sig_handler);
    signal(int SIGTSTP, driver_sig_handler);
    signal(int SIGINT, SIG_IGN);
    signal(int SIGQUIT, SIG_IGN);
    wait(NULL);
    exit(0);
  }
  while(1){
    pause();
  }
  return 0;
}
