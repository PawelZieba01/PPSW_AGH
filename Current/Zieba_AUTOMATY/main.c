#include "led.h"

void Delay(unsigned int uiDelayMilliseconds);



int main()
{
	enum LedShiftDir {SHIFT_LEFT, SHIFT_RIGHT};
	enum LedShiftDir eShiftDir = SHIFT_LEFT;

	unsigned short int usiShiftCounter = 0;

	LedInit();


	while(1)
	{
		switch(eShiftDir)
		{
			case SHIFT_LEFT:
				LedStepLeft();
				usiShiftCounter++;
			
				if(usiShiftCounter > 2)
				{
					eShiftDir = SHIFT_RIGHT;
				}
				else
				{
					eShiftDir = SHIFT_LEFT;
				}
				break;
			
			case SHIFT_RIGHT:
				LedStepRight();
				usiShiftCounter--;
			
				if(usiShiftCounter < 1)
				{
					eShiftDir = SHIFT_LEFT;
				}
				else
				{
					eShiftDir = SHIFT_RIGHT;
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
