#include "regx52.h"
#include "Timer0.h"
#include "key.h"
#include "INTRINS.H"

unsigned char Count=0;
unsigned char key_num = 0,led_mode = 0;

void Timer0_Rountine(void)  interrupt 1
{
	TL0 = 0x18;		
	TH0 = 0xFC;		
	Count++;
	
	if (Count > 100)
	{
		Count =0;	
		if (led_mode == 0)
		{
			P2=_crol_(P2,1);
		}
		if (led_mode == 1)
		{
			P2=_cror_(P2,1);
		}
	}

}

void main()
{
	Timer0_Init();
	P2 = 0xfe;
	while(1)
	{
		key_num = key();	
		
		if (key_num == 1)
		{
			led_mode++;
			if (led_mode>=2)
				led_mode = 0;
		}
	}
}