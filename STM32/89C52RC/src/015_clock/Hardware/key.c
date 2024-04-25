#include "regx51.h"
#include "Delay.h"
#include "key.h"

unsigned char key()
{
	unsigned char key_num = 0;
	
	if (P1_0 == 0) {Delay(20);while(P1_0 ==0);Delay(20);key_num=1;}
	if (P1_1 == 0) {Delay(20);while(P1_1 ==0);Delay(20);key_num=2;}
	if (P1_4 == 0) {Delay(20);while(P1_4 ==0);Delay(20);key_num=3;}
	if (P1_5 == 0) {Delay(20);while(P1_5 ==0);Delay(20);key_num=4;}
	
	return key_num;
}