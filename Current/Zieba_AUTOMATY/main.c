#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiDelayMilliseconds);



int main()
{
	enum LedState {STOP, SHIFT_RIGHT, SHIFT_LEFT};
	enum LedState eLedState = SHIFT_RIGHT;

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
				if(BUTTON_1 == eKeyboardRead())
				{
					eLedState = STOP;
				}
				else
				{
					LedStepLeft();
					eLedState = SHIFT_LEFT;
				}
				break;
			
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
