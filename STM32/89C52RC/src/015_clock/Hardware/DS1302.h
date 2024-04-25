#ifndef _DS1302_H_
#define _DS1302_H_

#define DS1302_SECOND	0X80
#define DS1302_MINUTE   0X82
#define DS1302_HOUR		0X84
#define DS1302_DATE		0X86
#define DS1302_MONTH	0X88
#define DS1302_DAY		0X8A
#define DS1302_YEAR		0X8C
#define DS1302_WP		0X8E

extern char DS1302_Time[];
void DS1302_Init(void);
void DS1302_WriteByte(unsigned char Command,unsigned char Data);
unsigned char DS1302_ReadByte(unsigned char Command);
void DS1302_TimeSet(void);
void DS1302_TimeRead(void);
#endif