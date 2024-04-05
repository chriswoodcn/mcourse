#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {
  int fd;

  fd = open("/dev/fs_chrdev", O_RDWR);
  if (fd < 0) {
    perror("open");
    return -1;
  }

  close(fd);

  return 0;
}