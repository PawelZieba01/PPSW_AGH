#include <LPC21xx.H>

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)
#define LED4_bm (1<<20)
#define LED5_bm (1<<21)
#define LED6_bm (1<<22)
#define LED7_bm (1<<23)

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
	IO1DIR = IODIR1 | LED3_bm;
	
	
	while(1)
	{
		IO1SET = IO1SET | LED3_bm;
		Delay(50);
		IO1CLR = IO1CLR | LED3_bm;
		Delay(50);
	}
}
//4.10
