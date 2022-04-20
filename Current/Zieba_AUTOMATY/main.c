#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiDelayMilliseconds);



int main()
{
	enum LedState {STOP, SHIFT};
	enum LedState eLedState = STOP;

	unsigned short int usiShiftCounter = 0;

	LedInit();


	while(1)
	{
		switch(eLedState)
		{
			case STOP:
				if(BUTTON_0 == eKeyboardRead())
				{
					eLedState = SHIFT;
				}
				else
				{
					eLedState = STOP;
				}
				break;
			
			case SHIFT:
				if(usiShiftCounter >= 3)
				{
					usiShiftCounter = 0;
					eLedState = STOP;
				}
				else
				{
					LedStepRight();
					usiShiftCounter++;
					eLedState = SHIFT;
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
