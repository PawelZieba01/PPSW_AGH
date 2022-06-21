#include "uart.h"
#include "servo.h"
#include "adc.h"
#include "string.h"
#include "led.h"

#define MapRange(a1,a2,b1,b2,s) (b1 + (s-a1)*(b2-b1)/(a2-a1))

/*******************************************/
int main()
{	
	char acBuffToSend[64] = "";
	unsigned int uiPotValue = 0;
	unsigned int uiServoPotPosition = 0;
	
	ServoInit(200);
	UART_InitWithInt(9600);
	ADCInit();

	while(1)
	{
		uiPotValue = ADCStartConversion();
		uiServoPotPosition = MapRange(0, 1023, 0, 35, uiPotValue);
		
		ServoGoTo(uiServoPotPosition);
		
		CopyString("ADC: ", acBuffToSend);
		AppendUIntToString(uiPotValue , acBuffToSend);
		
		AppendString("   ServoPos: ", acBuffToSend);
		AppendUIntToString(uiServoPotPosition , acBuffToSend);
		
		if(eTransmiter_GetStatus() == FREE)
		{
			Transmiter_SendString(acBuffToSend);
		}
	}
}
/*******************************************/
