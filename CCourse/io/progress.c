#include <stdio.h>
#include <unistd.h>

#define NUM 100

int main() {
  char buffer[NUM + 1] = {0}; // 存储进度条字符
  char arr[5] = {"-/|\\"};    // 存储基本变化字符
  for (int i = 0; i < NUM; i++) {
    buffer[i] = '#'; // 增加打印#
    printf("[%c][%-100s][%d%%]\r", arr[i % 4], buffer,
           i + 1);  //[#### ][8%][-] 这种格式
    fflush(stdout); // 强制刷新打印
    usleep(50000);  // 每次覆盖打印间隔1s
  }
  printf("\n");
  return 0;
}