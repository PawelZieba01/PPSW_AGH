#include "timer.h"
#include "led.h"


int main()
{
	LedInit();
	InitTimer0Match0(250000);
	
	while(1)
	{
		LedStepRight();
		WaitOnTimer0Match0();
	}
}
