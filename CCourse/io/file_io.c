#include <stdio.h>
#include <string.h>

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
int main(int argc, char *argv[]) {
  // test_fgets();
  // test_mock_cp(argc, argv);
  test_write();
  test_read();
  return 0;
}