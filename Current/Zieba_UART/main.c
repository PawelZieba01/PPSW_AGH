#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "led.h"

#define NULL '\0'

void Delay(unsigned int uiDelayMilliseconds);

/*******************************************/
int main()
{
	unsigned int uiServoPosition = 0;
	
	UART_InitWithInt(9600);
	//KeyboardInit();
	ServoInit(50);

	while(1)
	{
		//Delay(100);
		
		switch(cOdebranyZnak)
		{
			case '1':
				uiServoPosition = uiServoPosition + 12;
				ServoGoTo(uiServoPosition);
				cOdebranyZnak = NULL;
				break;
			
			case 'c':
				ServoCallib();
				uiServoPosition = 0;
				cOdebranyZnak = NULL;	//albo tutaj trzeba wpisac nulla albo u gory odkomentowac delaya
			
			default:
				break;
		}
		
		
		
		/*switch(eKeyboardRead())
		{
			case BUTTON_0:
				ServoCallib();
				break;
			
			case BUTTON_1:
				ServoGoTo(12);
				break;
			
			case BUTTON_2:
				ServoGoTo(24);
				break;
			
			case BUTTON_3:
				ServoGoTo(36);
				break;
	
			default:
				break;
		}  */              
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
