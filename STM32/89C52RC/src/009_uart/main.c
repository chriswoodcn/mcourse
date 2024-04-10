#include "regx52.h"
#include "Delay.h"
#include "UART.h"

void main()
{
	UART_Init();
	
	while(1)
	{
		UART_SendByte(0x33);
		Delay(10);
	}
}

