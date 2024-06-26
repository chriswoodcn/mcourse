#include "reg52.h"
#include "Delay.h"
#include <INTRINS.H>

sbit Max7219_CLK = P0^5;
sbit Max7219_CS = P0^4;
sbit Max7219_DIN = P0^6;

unsigned char disp[8] = {
	0x66,
	0xff,
	0xff,
	0xff,
	0xff,
	0x7e,
	0x3c,
	0x18
};
/**
 * 拆分一位位发送 高位先发送MSB
 */
void Write_MAX7219_Byte(unsigned dat) {
  unsigned char i = 0;
  Max7219_CS = 0;
  for (i = 8; i >= 1; i--) {
    Max7219_CLK = 0;
    Max7219_DIN = dat & 0x80;
    dat = dat << 1;
    Max7219_CLK = 1;
  }
}
/**
 * 向led点阵屏写数据
 */
void Write_MAX7219(unsigned char address, unsigned char dat) {
  Max7219_CS = 0;
  Write_MAX7219_Byte(address);
  Write_MAX7219_Byte(dat);
  Max7219_CS = 1;
}

void MAX7219_Init() {
  Write_MAX7219(0x0c, 0x01);
  Write_MAX7219(0x0f, 0x00);
  Write_MAX7219(0x0a, 0x03);
  Write_MAX7219(0x0b, 0x07);
  Write_MAX7219(0x09, 0x00);
}

unsigned char i;
void main() {
  MAX7219_Init();
  while (1) {
		Delay(200);
		for (i = 0; i < 8; i++) {
      disp[i]= _cror_(disp[i], 1);
		}
    for (i = 0; i < 8; i++) {
      Write_MAX7219(i + 1, disp[i]);
    }
  }
}