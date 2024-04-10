#include "regx52.h"

void Timer0_Init()
{
	TMOD &= 0xF0;	
	TMOD |= 0x01;		
	TL0 = 0x18;		
	TH0 = 0xFC;		
	TF0 = 0;		
	TR0 = 1;		
	ET0  = 1;
	EA   = 1;
	PT0  = 0;
}

//void Timer0_Rountine(void)  interrupt 1
//{
//	TL0 = 0x18;		
//	TH0 = 0xFC;		
//	Count++;
//	
//	if (Count > 100)
//	{
//		Count =0;	
//	}

//}