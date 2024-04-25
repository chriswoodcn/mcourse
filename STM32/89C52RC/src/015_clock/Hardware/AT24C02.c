#include "regx52.h"
#include "AT24C02.h"

sbit AT24C02_I2C_SCL=P4^3;
sbit AT24C02_I2C_SDA=P4^4;

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void I2C_Start()
{
	AT24C02_I2C_SCL=1;
	AT24C02_I2C_SDA=1;
	AT24C02_I2C_SDA=0;
	AT24C02_I2C_SCL=0;
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void I2C_Stop()
{
	AT24C02_I2C_SDA=0;
	AT24C02_I2C_SCL=1;
	AT24C02_I2C_SDA=1;
}


/**
  * @brief  I2C发送应答
  * @param  AckBit 应答位，0为应答，1为非应答
  * @retval 无
  */
void I2C_SendAsk(unsigned char AckBit)
{
	AT24C02_I2C_SDA=AckBit;
	AT24C02_I2C_SCL=1;
	AT24C02_I2C_SCL=0;
}

/**
  * @brief  I2C接收应答位
  * @param  无
  * @retval 接收到的应答位，0为应答，1为非应答
  */
unsigned char I2C_ReceiveAsk()
{
	unsigned char AckBit;
	
	AT24C02_I2C_SDA =1;
	AT24C02_I2C_SCL=1;
	AckBit=AT24C02_I2C_SDA;
	AT24C02_I2C_SCL=0;	
	
	return AckBit;
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的字节
  * @retval 无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	
	for(i=0;i<8;i++)
	{
		AT24C02_I2C_SDA=Byte&(0x80>>i);
		AT24C02_I2C_SCL=1;
		AT24C02_I2C_SCL=0;
	}
}

/**
  * @brief  I2C接收一个字节
  * @param  无
  * @retval 接收到的一个字节数据
  */
unsigned char I2C_Receive()
{
	unsigned char i,Byte=0x00;
	
	for(i=0;i<8;i++)
	{
		AT24C02_I2C_SCL=1;
		if (AT24C02_I2C_SDA)
		{
			Byte|= (0X80>>i); 
		}
		AT24C02_I2C_SCL=0;
	}
	return Byte;
}

/**
  * @brief  AT24C02写入一个字节
  * @param  WordAddress 要写入字节的地址
  * @param  Data 要写入的数据
  * @retval 无
  */
void AT24C02_WriteByte(unsigned char WordAddr,unsigned char Data)
{
	I2C_Start();
	I2C_SendByte(0xA0);
	I2C_ReceiveAsk();
	I2C_SendByte(WordAddr);
	I2C_ReceiveAsk();
	I2C_SendByte(Data);
	I2C_ReceiveAsk();
	I2C_Stop();
}
/**
  * @brief  AT24C02读取一个字节
  * @param  WordAddress 要读出字节的地址
  * @retval 读出的数据
  */
unsigned char AT24C02_ReadByte(unsigned char WordAddr)
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(0xA0);
	I2C_ReceiveAsk();
	I2C_SendByte(WordAddr);
	I2C_ReceiveAsk();
//	I2C_Stop();
	I2C_Start();
	I2C_SendByte(0xA1);	
	I2C_ReceiveAsk();
	Data=I2C_Receive();
	I2C_SendAsk(1);
	I2C_Stop();
	
	return Data;
}
