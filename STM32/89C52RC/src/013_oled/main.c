#include "oled.h"
#include "regx52.h"

sbit I2C_SDA = P4^6;
sbit I2C_SCL = P4^5;

unsigned char I2C_receive() {
  unsigned char Byte = 0x00;
  I2C_SDA = 1;
  for (int i = 0; i < 8; i++) {
    I2C_SCL = 1;
    if (I2C_SDA) {
      Byte |= (0x80 >> 1);
    }
    I2C_SCL = 0;
  }
  return Byte;
}

void main() {
  OLED_Init();
  OLED_ShowChar(1, 1, 'A');
  OLED_ShowChar(1, 3, 'a');
  OLED_ShowString(1, 4, "YourFun!");
  OLED_ShowNum(2, 1, 2397, 4);
  OLED_ShowSignedNum(2, 7, -2397, 4);
  OLED_ShowHexNum(3, 1, 0xff01, 4);
  // OLED_ShowBinNum(4,1,1111111100000001,16);
  OLED_ShowBinNum(4, 1, 0xff01, 16);
  while (1) {
  }
}