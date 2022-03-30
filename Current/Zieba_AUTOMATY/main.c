#include "led.h"

void Delay(unsigned int uiDelayMilliseconds);



int main()
{
	enum LedState {LED_LEFT, LED_RIGHT};
	enum LedState eLedState = LED_LEFT;

	LedInit();

	while(1)
	{
		switch(eLedState)
		{
			case LED_LEFT:
				eLedState = LED_RIGHT;
				LedStepRight();
				break;
			
			case LED_RIGHT:
				eLedState = LED_LEFT;
				LedStepLeft();
				break;
		}
		Delay(500);
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
