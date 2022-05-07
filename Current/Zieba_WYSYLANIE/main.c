#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"

void Delay(unsigned int uiDelayMilliseconds);

/*******************************************/
int main()
{	
	unsigned int uiCounter = 0;
	char acStringToSend[15]; 
	
	UART_InitWithInt(9600);
	
	while(1)
	{
		if(FREE == eTransmiter_GetStatus())
		{
			CopyString("licznik ", acStringToSend);
			AppendUIntToString(uiCounter, acStringToSend);
			
			Transmiter_SendString(acStringToSend);
			uiCounter++;
		}
		
		Delay(200);
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
