#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiDelayMilliseconds);
extern void LedOn(unsigned char ucLedIndeks);


int main()
{
	enum LedState {STOP, SHIFT_RIGHT, SHIFT_LEFT, BLINK};
	enum LedState eLedState = SHIFT_RIGHT;

	unsigned char ucBlinkCounter = 0;
	unsigned char fBlinkLedState = 0;

	LedInit();


	while(1)
	{
		switch(eLedState)
		{
			case STOP:
				if(BUTTON_0 == eKeyboardRead())
				{
					eLedState = SHIFT_LEFT;
				}
				else if(BUTTON_2 == eKeyboardRead())
				{
					eLedState = SHIFT_RIGHT;
				}
				else
				{
					eLedState = STOP;
				}
				break;
			
			case SHIFT_RIGHT:
				if(BUTTON_1 == eKeyboardRead())
				{
					eLedState = STOP;
				}
				else
				{
					LedStepRight();
					eLedState = SHIFT_RIGHT;
				}
				break;
				
			case SHIFT_LEFT:
				if(BUTTON_3 == eKeyboardRead())
				{
					eLedState = BLINK;
				}
				else if(BUTTON_1 == eKeyboardRead())
				{
					eLedState = STOP;
				}
				else
				{
					LedStepLeft();
					eLedState = SHIFT_LEFT;
				}
				break;
			
			case BLINK:
				if(ucBlinkCounter > 10)
				{
					ucBlinkCounter = 0;
					eLedState = SHIFT_RIGHT;
				}
				else
				{
					if(0 == fBlinkLedState)
					{
						LedOn(1);
						fBlinkLedState = 1;
					}
					else
					{
						LedOn(4); 
						fBlinkLedState = 0;
					}
					
					ucBlinkCounter++;
					eLedState = BLINK;
				}
				
			default:
				break;
		}
		Delay(100);
	}
}



void Delay(unsigned int uiDelayMilliseconds)
{
	unsigned int uiDelayCounter;
	
	for(; uiDelayMilliseconds > 0; uiDelayMilliseconds--)
	{
		for(uiDelayCounter = 0; uiDelayCounter < 7500; uiDelayCounter++){}
	}
}
