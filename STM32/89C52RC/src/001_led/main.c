#include <Delay.h>
#include <STC89xx.h>

/**
 * 51开发板 led流水灯
 */
int main(void) {
  unsigned char root = 0xFF;
  unsigned char magic = 0x1;
  while (1) {
    if (magic == 0)
      magic = 0x1;
    Delay(100);
    P2 = root & ~(magic);
    magic = magic << 1;
  }
}