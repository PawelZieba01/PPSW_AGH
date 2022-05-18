#include "timer.h"
#include <LPC21xx.H>

#define COUNTER_ENABLE_BIT (1<<0)
#define COUNTER_RESET_BIT (1<<1)
#define INTERRUPT_ON_MR0_BIT (1<<0)
#define RESET_ON_MR0_BIT (1<<1)
#define MR0_INTERRUPT_FLAG_BIT (1<<0)

void InitTimer0(void)
{
	T0TCR |= COUNTER_ENABLE_BIT;
}

void WaitOnTimer(unsigned int iDelayTime)
{
	unsigned int uiStopValue = iDelayTime * 15;
	
	T0TCR &= ~COUNTER_RESET_BIT;
	T0TCR |= COUNTER_RESET_BIT;
	while(T0TC < uiStopValue){}
	
}

void InitTimer0Match0(unsigned int iDelayTime)
{
	unsigned int uiStopValue = iDelayTime * 15;
	
	T0MR0 = uiStopValue;
	T0MCR |= RESET_ON_MR0_BIT | INTERRUPT_ON_MR0_BIT;
	
	T0TCR &= ~COUNTER_RESET_BIT;
	T0TC = 0;
	T0TCR |= COUNTER_ENABLE_BIT;
}

void WaitOnTimer0Match0(void)
{
	while((T0IR & MR0_INTERRUPT_FLAG_BIT) == 0){}
	T0IR = MR0_INTERRUPT_FLAG_BIT;
}
