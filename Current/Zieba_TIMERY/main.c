#include "timer.h"
#include "led.h"


int main()
{
	LedInit();
	
	while(1)
	{
		LedStepRight();
		WaitOnTimer(250000);
	}
}
