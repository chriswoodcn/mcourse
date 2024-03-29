#include <stdio.h>

unsigned long ByteSwap(unsigned long val) {
  int ch;

  asm volatile(
      "eor r3, %1, %1, ror #16\n\t" // 循环右移16位  放到高16位上
                                    // 0x00001234与0x12340000做异或 r3=
                                    // 0x12341234
      "bic r3, r3, #0x00ff0000\n\t" // 位清除  r3 = 0x12001234
      "mov %0, %1, ror #8\n\t" // 0x00001234循环右移8位 参数 = 0x34000012
      "eor %0, %0, r3, lsr #8" // r3逻辑右移8位 0x00120012与参数0x34000012做异或
                               // 参数=0x34120000
      : "=r"(ch)
      : "%0"(val)
      : "r3");
}
int main(void) {
  unsigned long test_a = 0x1234, result;

  result = ByteSwap(test_a);

  printf("Result:%d\r\n", result);

  return 0;
}