#include <LPC21xx.H>

void Delay()
{
	unsigned long int uliDelayCounter;
	
	for(uliDelayCounter = 0; uliDelayCounter < 7500000; uliDelayCounter++){}
}

int main()
{
	IO1DIR = IODIR1 | (1<<16);
	
	
	while(1)
	{
		IO1SET = IO1SET | (1<<16);
		Delay();
		IO1CLR = IO1CLR | (1<<16);
		Delay();
	}
}
