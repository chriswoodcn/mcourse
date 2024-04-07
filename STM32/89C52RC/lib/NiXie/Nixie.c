#include "Nixie.h"
#include <STC89xx.h>
#include <Delay.h>

unsigned int smgvalue[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,

 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};


void Nixie(unsigned char id,unsigned char value,int count)
{
	switch (id)
	{
		case 1:P36 = 1, P35 = 0; P34 = 0;  break;
		case 2:P36 = 1, P35 = 0; P34 = 1;  break;
		case 3:P36 = 1, P35 = 1; P34 = 0;  break;
		case 4:P36 = 1, P35 = 1; P34 = 1;  break;
		case 5:P36 = 0, P35 = 0; P34 = 0;  break;
		case 6:P36 = 0, P35 = 0; P34 = 1;  break;
		case 7:P36 = 0, P35 = 1; P34 = 0;  break;
		case 8:P36 = 0, P35 = 1; P34 = 1;  break;
		default:break;
	}
	P0 = smgvalue[value];
	Delay(count);
	P0 = 0x00;
}
