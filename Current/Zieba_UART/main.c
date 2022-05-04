#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "led.h"


/*******************************************/
int main()
{
	UART_InitWithInt(9600);
	LedInit();
	KeyboardInit();
	ServoInit(50);

	while(1)
	{
		switch(cOdebranyZnak)
		{
			case '1':
				ServoGoTo(12);
				break;
			
			case '2':
				ServoGoTo(24);
				break;
			
			case '3':
				ServoGoTo(36);
				break;
			
			case 'c':
				ServoCallib();
			
			default:
				break;
		}
		
		switch(eKeyboardRead())
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
		}  
		
		/*switch(cOdebranyZnak)
		{
			case '1':
				LedOn(0);
				break;
			
			case '2':
				LedOn(1);
				break;
			
			case '3':
				LedOn(2);
				break;
			
			case '4':
				LedOn(3);
				break;
			
			case 'c':
				LedOn(4);
			
			default:
				break;
		}*/                 
	}
}
/*******************************************/
