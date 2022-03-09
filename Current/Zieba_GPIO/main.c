#include <LPC21xx.H>
#define LED_0_bm (1<<16)

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
	IO1DIR = IODIR1 | LED_0_bm;
	
	
	while(1)
	{
		IO1SET = IO1SET | LED_0_bm;
		Delay(50);
		IO1CLR = IO1CLR | LED_0_bm;
		Delay(50);
	}
}
//4.8
