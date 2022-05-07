#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"

void Delay(unsigned int uiDelayMilliseconds);

/*******************************************/
int main()
{	
	UART_InitWithInt(9600);
	
	while(1)
	{
		if(FREE == eTransmiter_GetStatus())
		{
			Transmiter_SendString("test123\n\r");
		}
	}
}
/*******************************************/


void Delay(unsigned int uiDelayMilliseconds)
{
	unsigned int uiDelayCounter;
	
	for(; uiDelayMilliseconds > 0; uiDelayMilliseconds--)
	{
		for(uiDelayCounter = 0; uiDelayCounter < 7500; uiDelayCounter++){}
	}
}
