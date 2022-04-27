#include <LPC21xx.H>
#include "keyboard.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETECTOR_PIN (1<<10)

enum DetectorState {ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo
{
	enum ServoState eState; 
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
}; 

struct Servo sServo;


void DetectorInit(void);
enum DetectorState eReadDetector(void);
void Automat(void);

/*******************************************/
int main()
{
	LedInit();
	KeyboardInit();
	DetectorInit();
	Timer0Interrupts_Init(20000, &Automat);

	while(1)
	{
		switch(eKeyboardRead())
		{
			case BUTTON_0:
				sServo.eState = CALLIB;
				break;
			
			case BUTTON_1:
				sServo.uiDesiredPosition = 12;
				break;
			
			case BUTTON_2:
				sServo.uiDesiredPosition = 24;
				break;
			
			case BUTTON_3:
				sServo.uiDesiredPosition = 36;
				break;
	
			default:
				break;
		}
	}
}
/*******************************************/


void Automat(void)
{
	switch(sServo.eState)
	{
		case IDLE:
			if(sServo.uiCurrentPosition != sServo.uiDesiredPosition)
			{
				sServo.eState = IN_PROGRESS;
			}
			else
			{
				sServo.eState = IDLE;
			}
			break;
		
		case IN_PROGRESS:
			if(sServo.uiCurrentPosition < sServo.uiDesiredPosition)
			{
				LedStepRight();
				sServo.uiCurrentPosition++;
				sServo.eState = IN_PROGRESS;
			}
			else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition)
			{
				LedStepLeft();
				sServo.uiCurrentPosition--;
				sServo.eState = IN_PROGRESS;
			}
			else
			{
				sServo.eState = IDLE;
			}
			break;
		
		case CALLIB:
			if(ACTIVE == eReadDetector())
			{
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;
				sServo.eState = IDLE;
			}
			else
			{
				LedStepLeft();
				sServo.eState = CALLIB;
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
