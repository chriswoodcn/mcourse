#include "regx52.h"
#include "oled.h"
#include "key.h"
#include "AT24C02.h"

unsigned char Num=30,key_num = 0;
void main()
{
	OLED_Init();
	OLED_Clear();
	
	while(1)
	{
		OLED_ShowNum(1,1,Num,3);
		
		key_num = key();
		
		if (key_num)
		{
			if (key_num == 1)
			{
				AT24C02_WriteByte(0,Num);
				OLED_ShowNum(2,1,Num,3);
				OLED_ShowString(2,6,"W_OK");
			}
			if (key_num == 2)
			{
				Num = AT24C02_ReadByte(0);
				OLED_ShowNum(3,1,Num,3);
				OLED_ShowString(3,6,"R_OK");
			}			
			if (key_num == 3)
			{
				Num++;
				OLED_ShowNum(1,1,Num,3);
			}
			if (key_num == 4)
			{
				Num--;
				OLED_ShowNum(1,1,Num,3);
			}
		}
	}
}

