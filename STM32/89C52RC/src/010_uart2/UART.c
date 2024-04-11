#include "regx52.h"

void UART_Init() // 4800bps@12.000MHz
{
  SCON = 0X50;
  PCON |= 0x80;
  TMOD &= 0x0F;
  TMOD |= 0x20;
  TL1 = 0xF3;
  TH1 = 0xF3;
  ET1 = 0;
  TR1 = 1;
  ES = 1;
  EA = 1;
}

void UART_SendByte(unsigned char Byte) {
  // 放入缓存寄存器
  SBUF = Byte;
  while (TI == 0) {
  };
  // 软件复位
  TI = 0;
}

void UART_Routine() interrupt 4 {
  // 读取缓存寄存器
  if (RI == 1) {
    P2 = ~SBUF;
    UART_SendByte(SBUF);
    // 软件复位
    RI = 0;
  }
}
