#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
  fd_set fs, temp;
  FD_ZERO(&fs);
  FD_ZERO(&temp);
  struct timeval tv = {
      .tv_sec = 1,
      .tv_usec = 0,
  };

  int mouse0 = open("/dev/input/mouse1", O_RDONLY);
  int mouse1 = open("/dev/input/mouse1", O_RDONLY);
  FD_SET(0, &fs);
  if (mouse0 > 0)
    FD_SET(mouse0, &fs);
  if (mouse1 > 0)
    FD_SET(mouse1, &fs);

  int val;
  char buf[128] = {0};
  while (1) {
    // 因为select 函数返回之后会自动将除了产生事件的文件描述符以外的位全部清除
    // 所以使用临时的temp
    temp = fs;
    val = select(mouse1 + 1, &temp, NULL, NULL, NULL);
    if (val < 0) {
      perror("select error");
      exit(-1);
    }
    if (FD_ISSET(0, &temp)) {
      sleep(1);
      // read(stdin, buf, sizeof(buf));
      fgets(buf, sizeof(buf), stdin);
      printf("this is keyboard event\n");
    }
    if (mouse0 > 0 && FD_ISSET(mouse0, &temp)) {
      sleep(1);
      // read(mouse0, buf, sizeof(buf));
      fgets(buf, sizeof(buf), mouse0);
      printf("this is mouse0 event\n");
    }
    if (mouse1 > 0 && FD_ISSET(mouse1, &temp)) {
      sleep(1);
      // read(mouse1, buf, sizeof(buf));
      fgets(buf, sizeof(buf), mouse1);
      printf("this is mouse1 event\n");
    }
  }
  if (mouse0 > 0)
    close(mouse0);
  if (mouse1 > 0)
    close(mouse1);
  return 0;
}