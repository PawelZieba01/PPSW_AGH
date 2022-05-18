#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

enum LedState {STOP, SHIFT_RIGHT, SHIFT_LEFT};
enum LedState eLedState = SHIFT_RIGHT;

void Automat()
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
}

int main()
{
	unsigned int iMainLoopCtr;
	
	LedInit();
	KeyboardInit();
	Timer0Interrupts_Init(250000, &Automat);

	while(1)
	{
	 	iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++;
	}
}
