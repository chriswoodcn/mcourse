#include "regx52.h"
/**
 * 串口相关寄存器
 * SCON 串口配置
 * SBUF 串口数据缓存
 * PCON 电源控制寄存器
 * IE 使能中断
 * IPH 中断优先级高寄存器
 * IP 中断优先级低寄存器
 * SADEN slave address mask
 * SADDR slave address
 */
void UART_Init() // 4800bps@12.000MHz
{
  SCON = 0X40;
  PCON |= 0x80;
  TMOD &= 0x0F;
  TMOD |= 0x20;
  TL1 = 0xF3;
  TH1 = 0xF3;
  ET1 = 0;
  TR1 = 1;
}

void UART_SendByte(unsigned char Byte) {
  SBUF = Byte;
  while (TI == 0)
    ;
  TI = 0;
}