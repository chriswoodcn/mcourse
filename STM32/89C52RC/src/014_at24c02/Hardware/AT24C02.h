#ifndef _AT24C02_H_
#define _AT24C02_H_

void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendAsk(unsigned char AckBit);
unsigned char I2C_ReceiveAsk(void);
void I2C_SendByte(unsigned char Byte);
unsigned char I2C_Receive(void);
void AT24C02_WriteByte(unsigned char WordAddr,unsigned char Data);
unsigned char AT24C02_ReadByte(unsigned char WordAddr);
#endif