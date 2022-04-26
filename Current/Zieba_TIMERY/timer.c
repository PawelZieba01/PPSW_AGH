#include "timer.h"
#include <LPC21xx.H>

#define COUNTER_ENABLE_BIT (1<<0)
#define COUNTER_RESET_BIT (1<<1)

void InitTimer0(void)
{
	T0TCR &= ~COUNTER_RESET_BIT;
	T0TCR |= COUNTER_ENABLE_BIT;
}

void WaitOnTimer(unsigned long int uliPeriod)
{
	unsigned long int uliStopValue = uliPeriod * 15;
	
	InitTimer0();
	while(T0TC < uliStopValue){}
		
	T0TCR |= COUNTER_RESET_BIT;
}
