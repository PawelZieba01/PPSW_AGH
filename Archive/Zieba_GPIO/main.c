#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiDelayMilliseconds)
{
	unsigned int uiDelayCounter;
	
	for(; uiDelayMilliseconds > 0; uiDelayMilliseconds--)
	{
		for(uiDelayCounter = 0; uiDelayCounter < 7500; uiDelayCounter++){}
	}
}


//5.2
int main()
{	
	LedInit();
	
	while(1)
	{
		Delay(250);
		switch(eKeyboardRead())
		{
			case BUTTON_1:
				LedStepRight();
				break;
			
			case BUTTON_2:
				LedStepLeft();
				break;	
			
			default:
				break;
		}

	}
}

