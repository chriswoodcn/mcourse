#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/// 测试fgets使用
void test_fgets() {
  char buf[32] = {0};
  while (1) {
    char *gets = fgets(buf, 10, stdin);
    int compare = strcmp("exit\n", buf);
    if (compare == 0) {
      break;
    }
    printf("%s\n", buf);
  }
}
/// 测试模拟cp命令
void test_mock_cp(int argc, char *argv[]) {
  FILE *f_src, *f_dest;
  if ((f_src = fopen(argv[1], "r")) == NULL) {
    perror("open f_src error");
    return;
  }
  if ((f_dest = fopen(argv[2], "w")) == NULL) {
    perror("open f_dest error");
    return;
  }
  char buf[64] = {0};
  while (fgets(buf, 64, f_src) != NULL) {
    fputs(buf, f_dest);
  }
  fclose(f_src);
  fclose(f_dest);
}
/// 测试fwrite
void test_write() {
  float ft[5] = {10.00, 20.00, 36.15, 15.55};
  FILE *dest = fopen("./ft.o", "w+");
  size_t res = fwrite(ft, sizeof(float), 3, dest);
  printf("fwrite res = %d\n", res);
  fclose(dest);
}
/// 测试fread
void test_read() {
  float ft[5] = {0};
  FILE *dest = fopen("./ft.o", "r");
  size_t res = fread(ft, sizeof(float), 3, dest);
  printf("fread res = %d\n", res);
  for (int i = 0; i < res; i++) {
    printf("ft[%d] = %.2f\n", i, ft[i]);
  }
  puts("");
  fclose(dest);
}
/// 测试向文件输出
void test_log() {
  char temp[64] = {0};
  int line_num = 0;
  time_t t;
  struct tm *tm;

  FILE *fp = fopen("./test.log", "a+");
  if (fp == NULL) {
    perror("fopen test.log error");
    return;
  }
  while (fgets(temp, 64, fp) != NULL) {
    printf("buf = %s\n", temp);
    if (temp[strlen(temp) - 1] == '\n')
      line_num++;
  }
  printf("line_num = %d\n", line_num);
  int num;
  while (1) {
    time(&t);
    tm = localtime(&t);
    num = ++line_num;
    printf("%d、%04d-%02d-%02d %02d:%02d:%02d\n", num, tm->tm_year + 1900,
           tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    fprintf(fp, "%d、%04d-%02d-%02d %02d:%02d:%02d\n", num, tm->tm_year +
    1900,
            tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min,
            tm->tm_sec);
    fflush(NULL);
    sleep(1);
  }
}
int main(int argc, char *argv[]) {
  // test_fgets();
  // test_mock_cp(argc, argv);
  // test_write();
  // test_read();
  test_log();
  return 0;
}