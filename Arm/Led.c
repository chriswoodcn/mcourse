#include "stm32mp1xx_gpio.h"

void mydelay_ms(int ms) {
  volatile int i = 0, j = 0;
  while (ms--) {
    for (i = 0; i < 1000; i++)
      for (j = 0; j < 1000; j++)
        ;
  }
}

int main() {
  GPIOZ->MODER = (GPIOZ->MODER &= ~(0x3 << 10)) | 0x1 << 10; // 设置为输出模式
  GPIOZ->OTYPER &= ~(0x1 << 5);                              // 推娩输出

  GPIOZ->OSPEEDR &= ~(0x3 << 10); // 低速
  while (1) {
    GPIOZ->ODR = (GPIOZ->ODR &= ~(0x1 << 5)) | 0x1 << 5;
    mydelay_ms(30);

    GPIOZ->ODR &= ~(0x1 << 5);
    mydelay_ms(30);
  }
  return 0;
}