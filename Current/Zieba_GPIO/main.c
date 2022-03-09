#include <LPC21xx.H>

void Delay(unsigned int uiDelayMilliseconds) 															//ok 65 sekund chyba wystarczy - uint
{
	unsigned int uiDelayCounter;
	
	for(; uiDelayMilliseconds > 0; uiDelayMilliseconds--)										//dwie petle bo mnozenie troche zajmuje
	{
			for(uiDelayCounter = 0; uiDelayCounter < 7500; uiDelayCounter++){}
	}
}


int main()
{
	IO1DIR = IODIR1 | (1<<16);
	
	
	while(1)
	{
		IO1SET = IO1SET | (1<<16);
		Delay(1001);
		IO1CLR = IO1CLR | (1<<16);
		Delay(1001);
	}
}
