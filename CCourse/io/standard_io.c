#include <errno.h>
#include <stdio.h>
#include <string.h>

void compute_buff_size_1() {
  for (int i = 0; i < 1025; i++) {
    if (i < 10) {
      printf("000%d", i);
    } else if (i < 100) {
      printf("00%d", i);
    } else if (i < 1000) {
      printf("0%d", i);
    } else {
      printf("%d", i);
    }
  }
  // 通过printf结合打印出来的字符计算出缓存区大小为
  // 1024 * 4 = 4096字节
  while (1) {
  }
}
void compute_buff_size_2() {
  printf("");
  // ubuntu18.04
  // int stdout_size = stdout->_IO_buf_end - stdout->_IO_buf_base;
}
int test_fopen_1() {
  FILE *fp = NULL;
  fp = fopen("./test.txt", "r");
  if (fp == NULL) {
    printf("fopen fail\n");
    return -1;
  }
  printf("fopen success\n");
  return 0;
}

int test_fopen_2() {
  FILE *fp = NULL;
  fp = fopen("./test.txt", "w+");
  if (fp == NULL) {
    printf("fopen fail\n");
    return -1;
  }
  printf("bufsize: %d\n", fp->_bufsiz);
  int res = fclose(fp);
  printf("fclose res = %d\n", res);
}
int test_fopen_3() {
  FILE *fp = NULL;
  fp = freopen("./test.txt", "a+", stdout);
  if (fp == NULL) {
    // printf("freopen fail\n");
    perror("freopen fail\n");
    return -1;
  }
  printf("after freopen\n");
  fp = freopen("/dev/tty", "w+", stdout);
  // fclose(fp);
  return 0;
}
int main(int argc, char *argv[]) {
  // printf("hello standard io\n");
  // compute_buff_size_1();
  // test_fopen_1();
  // test_fopen_2();
  test_fopen_3();
  printf("strerror = %s\n", strerror(EINVAL));
  return 0;
}