#include "regx52.h"
#include "oled.h"
#include "DS1302.h"
#include "key.h"
#include "Timer0.h"

unsigned char time,KeyNum,MODE,TimeSetSelect,Flag500Ms = 0;
void TimeShow()
{
	DS1302_TimeRead();
	OLED_ShowNum(1,1,DS1302_Time[0], 2);
	OLED_ShowNum(1,4,DS1302_Time[1], 2);
	OLED_ShowNum(1,7,DS1302_Time[2], 2);
	OLED_ShowNum(2,1,DS1302_Time[3], 2);
	OLED_ShowNum(2,4,DS1302_Time[4], 2);
	OLED_ShowNum(2,7,DS1302_Time[5], 2);	
}

void TimeSet()
{
	if (KeyNum == 2)
	{
		TimeSetSelect++;
		TimeSetSelect %= 6;
	}
	if (KeyNum == 3)
	{
		DS1302_Time[TimeSetSelect]++;	
		if (DS1302_Time[0]>99){DS1302_Time[0]=0;} //年越界判断
		if (DS1302_Time[1]>12){DS1302_Time[1]=1;} //月越界判断
		
		if (DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 || DS1302_Time[1] == 7 ||  //大月判断
			DS1302_Time[1] == 8 || DS1302_Time[1] == 10 || DS1302_Time[1] == 12)
		{
			if (DS1302_Time[2]>31){DS1302_Time[2]=1;} //日越界判断
		}
		else if (DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time[1] == 9 || DS1302_Time[1] == 11) //小月判断
		{
			if (DS1302_Time[2]>30){DS1302_Time[2]=1;} //日越界判断
		}
		else if (DS1302_Time[1] == 2)
		{
			if (DS1302_Time[0] % 4 == 0)  //闰年
			{
				if (DS1302_Time[2]>29){DS1302_Time[2]=1;} //日越界判断
			}
			else  //非闰年
			{
				if (DS1302_Time[2]>28){DS1302_Time[2]=1;} //日越界判断
			}
		}
		
		if (DS1302_Time[3]>23){DS1302_Time[3]=0;} //时越界判断
		if (DS1302_Time[4]>59){DS1302_Time[4]=0;} //分越界判断
		if (DS1302_Time[5]>59){DS1302_Time[5]=0;} //秒越界判断
	}
	if (KeyNum == 4)
	{
		DS1302_Time[TimeSetSelect]--;	
		if (DS1302_Time[0]<0){DS1302_Time[0]=99;}//年越界判断
		if (DS1302_Time[1]<1){DS1302_Time[1]=12;} //月越界判断
		if (DS1302_Time[1] == 1 || DS1302_Time[1] == 3 || DS1302_Time[1] == 5 || DS1302_Time[1] == 7 ||  //大月判断
			DS1302_Time[1] == 8 || DS1302_Time[1] == 10 || DS1302_Time[1] == 12)
		{
			if (DS1302_Time[2]<1){DS1302_Time[2]=31;} //日越界判断
		}
		else if (DS1302_Time[1] == 4 || DS1302_Time[1] == 6 || DS1302_Time[1] == 9 || DS1302_Time[1] == 11) //小月判断
		{
			if (DS1302_Time[2]<1){DS1302_Time[2]=30;} //日越界判断
		}
		else if (DS1302_Time[1] == 2)
		{
			if (DS1302_Time[0] % 4 == 0)  //闰年
			{
				if (DS1302_Time[2]<1){DS1302_Time[2]=29;} //日越界判断
			}
			else  //非闰年
			{
				if (DS1302_Time[2]<1){DS1302_Time[2]=28;} //日越界判断
			}
		}
		if (DS1302_Time[3]<0){DS1302_Time[3]=23;} //时越界判断
		if (DS1302_Time[4]<0){DS1302_Time[4]=59;} //分越界判断
		if (DS1302_Time[5]<0){DS1302_Time[5]=59;} //秒越界判断
	}
	if (TimeSetSelect == 0 && Flag500Ms == 1){OLED_ShowString(1,1,"  ");}
	else {OLED_ShowNum(1,1,DS1302_Time[0], 2);}
	if (TimeSetSelect == 1 && Flag500Ms == 1){OLED_ShowString(1,4,"  ");}
	else {OLED_ShowNum(1,4,DS1302_Time[1], 2);}
	if (TimeSetSelect == 2 && Flag500Ms == 1){OLED_ShowString(1,7,"  ");}
	else {OLED_ShowNum(1,7,DS1302_Time[2], 2);}	
	if (TimeSetSelect == 3 && Flag500Ms == 1){OLED_ShowString(2,1,"  ");}
	else {OLED_ShowNum(2,1,DS1302_Time[3], 2);}		
	if (TimeSetSelect == 4 && Flag500Ms == 1){OLED_ShowString(2,4,"  ");}
	else {OLED_ShowNum(2,4,DS1302_Time[4], 2);}			
	if (TimeSetSelect == 5 && Flag500Ms == 1){OLED_ShowString(2,7,"  ");}
	else {OLED_ShowNum(2,7,DS1302_Time[5], 2);}				
}

void main()
{
	OLED_Init();
	OLED_ShowString(1,1,"RTC");
	DS1302_Init();
	DS1302_TimeSet();
	Timer0_Init();
	OLED_ShowChar(1,3,'-');
	OLED_ShowChar(1,6,'-');
	OLED_ShowChar(2,3,':');
	OLED_ShowChar(2,6,':');	
	while(1)
	{
		KeyNum=key();
		
		if (KeyNum == 1)
		{
			if (MODE == 0) //当前模式为 时钟运行模式
			{
				MODE = 1;//切换模式为 调节时间模式
			}
			else if(MODE == 1) //当前模式为 调节时间模式
			{
				MODE = 0; //切换模式为 时钟运行模式
				TimeSetSelect = 0;
				DS1302_TimeSet();
			}
		}
		
		switch (MODE)
		{
			case 0:TimeShow();break;
			case 1:TimeSet();break;
			default:break;
		}

	}
}

unsigned int Count=0;
void Timer0_Rountine(void)  interrupt 1
{
	TL0 = 0x18;		
	TH0 = 0xFC;		
	Count++;
	
	if (Count >= 500) 
	{
		Count =0;	
		Flag500Ms=!Flag500Ms;
	}
}