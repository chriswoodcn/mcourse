#include <Delay.h>
#include <Nixie.h>
#include <STC89xx.h>

unsigned char MatrixKey()
{
	unsigned char KeyNumber=0;
	
	P1 = 0xff;
	P13 = 0;
	if (P17==0){Delay(20);while(P17==0);Delay(20);KeyNumber=1;}
	if (P16==0){Delay(20);while(P16==0);Delay(20);KeyNumber=5;}
	if (P15==0){Delay(20);while(P15==0);Delay(20);KeyNumber=9;}
	if (P14==0){Delay(20);while(P14==0);Delay(20);KeyNumber=13;}
	
	P1 = 0xff;
	P12 = 0;
	if (P17==0){Delay(20);while(P17==0);Delay(20);KeyNumber=2;}
	if (P16==0){Delay(20);while(P16==0);Delay(20);KeyNumber=6;}
	if (P15==0){Delay(20);while(P15==0);Delay(20);KeyNumber=10;}
	if (P14==0){Delay(20);while(P14==0);Delay(20);KeyNumber=14;}
	
	P1 = 0xff;
	P11 = 0;
	if (P17==0){Delay(20);while(P17==0);Delay(20);KeyNumber=3;}
	if (P16==0){Delay(20);while(P16==0);Delay(20);KeyNumber=7;}
	if (P15==0){Delay(20);while(P15==0);Delay(20);KeyNumber=11;}
	if (P14==0){Delay(20);while(P14==0);Delay(20);KeyNumber=15;}
	
	P1 = 0xff;
	P10 = 0;
	if (P17==0){Delay(20);while(P17==0);Delay(20);KeyNumber=4;}
	if (P16==0){Delay(20);while(P16==0);Delay(20);KeyNumber=8;}
	if (P15==0){Delay(20);while(P15==0);Delay(20);KeyNumber=12;}
	if (P14==0){Delay(20);while(P14==0);Delay(20);KeyNumber=16;}
	
	return KeyNumber;
}
void main() {
	unsigned char KeyNum = 0;
	NiXie_init();
	while(1)
	{
		KeyNum = MatrixKey();
		if (KeyNum != 0)
		{
			NiXie(1,KeyNum);
		}
	}
}