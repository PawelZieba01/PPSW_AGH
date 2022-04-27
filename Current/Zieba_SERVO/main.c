#include <LPC21xx.H>
#include "keyboard.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETECTOR_PIN (1<<10)

enum DetectorState {ACTIVE, INACTIVE};

enum LedState {STOP, SHIFT_RIGHT, SHIFT_LEFT, CALLIB};
enum LedState eLedState = CALLIB;

void DetectorInit(void);
enum DetectorState eReadDetector(void);
void Automat(void);

/*******************************************/
int main()
{
	unsigned int iMainLoopCtr;
	
	LedInit();
	KeyboardInit();
	DetectorInit();
	Timer0Interrupts_Init(20000, &Automat);

	while(1)
	{
	 	iMainLoopCtr++;
	}
}
/*******************************************/


void Automat(void)
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
		
		case CALLIB:
			if(ACTIVE == eReadDetector())
			{
				eLedState = STOP;
			}
			else
			{
				LedStepLeft();
				eLedState = CALLIB;
			}
			break;
		
		default:
			break;
	}
}


void DetectorInit(void)
{
	IO0DIR &= ~DETECTOR_PIN;
}


enum DetectorState eReadDetector(void)
{
	if(0 == (IO0PIN & DETECTOR_PIN))
	{
		return ACTIVE;
	}
	else
	{
		return INACTIVE;
	}
}
