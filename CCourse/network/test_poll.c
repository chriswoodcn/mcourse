#include <fcntl.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#define N 2
#define BUF_SIZE 128
void poll_fd() {
  struct pollfd fds[N];
  fds[0].fd = 0;
  fds[0].events = POLLIN;
  int mouse1 = open("/dev/input/mouse1", O_RDONLY);
  fds[1].fd = mouse1;
  fds[1].events = POLLIN;
  int res;
  char buf[BUF_SIZE] = {0};
  while (1) {
    res = poll(&fds, N, 1000);
    if (res < 0) {
      perror("poll error");
      break;
    }
    if (res == 0) {
      printf("time out\n");
      contine;
    }
    for (int i = 0; i < N; i++) {
      if (fds[i].revents == POLLIN) {
        if (i == 0) {
          // 键盘读事件
          printf("键盘读事件\n");
          fgets(buf, BUF_SIZE, i);
          printf("buf = %s \n", buf);
        }
        if (i == 1) {
          // 鼠标读事件
          printf("鼠标读事件\n");
          read(mouse1, buf, BUF_SIZE, i);
          printf("buf = %s \n", buf);
        }
      }
    }
  }
}

int main() {
  poll_fd();
  return 0;
}