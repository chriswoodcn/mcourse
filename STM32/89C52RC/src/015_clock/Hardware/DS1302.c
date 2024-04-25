#include "regx52.h"
#include "DS1302.h"

sbit DS1302_CE = P3^4;
sbit DS1302_IO = P3^5;
sbit DS1302_SCLK = P3^6;

char DS1302_Time[]={22,12,13,21,13,5,2};

void DS1302_Init()
{
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

void DS1302_WriteByte(unsigned char Command,unsigned char Data)  
{
	unsigned char i;

	DS1302_CE = 1;
	for (i=0; i <8; i++)
	{
		DS1302_IO = Command&(0x01<<i);
		DS1302_SCLK= 1;
		DS1302_SCLK=0;
	}
	for (i=0; i <8; i++)
	{
		DS1302_IO = Data&(0x01<<i);
		DS1302_SCLK= 1;
		DS1302_SCLK=0;
	}
	DS1302_CE = 0;
}

unsigned char DS1302_ReadByte(unsigned char Command) 
{
	unsigned char Data = 0x00,i;
	Command |= 0X01;
	DS1302_CE = 1;
	for (i=0; i <8; i++)
	{
		DS1302_IO = Command&(0x01<<i);
		DS1302_SCLK=0;
		DS1302_SCLK=1;
	}
	for (i = 0; i<8; i++)
	{
		DS1302_SCLK=1;
		DS1302_SCLK=0;
		if (DS1302_IO) {Data |=(0x01<<i);}
	}
	DS1302_CE = 0;
	DS1302_IO = 0;
	return Data;
}

void DS1302_TimeSet()
{
	DS1302_WriteByte(DS1302_WP,0x00);
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x01);	
}

void DS1302_TimeRead()
{
	unsigned char temp;
	temp=DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5]=temp/16*10+temp%16;
	temp=DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6]=temp/16*10+temp%16;
}