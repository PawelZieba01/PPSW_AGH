#include <LPC21xx.H>

void Delay()
{
	unsigned int uiDelayCounter;
	
	for(uiDelayCounter = 0; uiDelayCounter < 1000; uiDelayCounter++){}
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
