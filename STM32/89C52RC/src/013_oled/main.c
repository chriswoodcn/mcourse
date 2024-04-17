#include "regx52.h"
#include "oled.h"

void main()
{
	OLED_Init();
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,4,"YourFun!");
	OLED_ShowNum(2,1,2397,4);
	OLED_ShowSignedNum(2,7,-2397,4);
	OLED_ShowHexNum(3,1,0xff01,4);
	OLED_ShowBinNum(4,1,1111111100000001,16);
	while(1)
	{

	}
}