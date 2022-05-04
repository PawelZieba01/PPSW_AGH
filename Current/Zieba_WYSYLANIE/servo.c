#include <LPC21xx.H>
#include "servo.h"
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


void ServoInit(unsigned int uiServoFrequency)
{
	LedInit();
	DetectorInit();
	sServo.eState = CALLIB;
	Timer0Interrupts_Init(1000000/uiServoFrequency, &Automat);
}


void ServoCallib(void)
{
	sServo.eState = CALLIB;
}


void ServoGoTo(unsigned int uiPosition)
{
	sServo.uiDesiredPosition = uiPosition;
}
