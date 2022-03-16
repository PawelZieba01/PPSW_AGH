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

void LedInit()
{
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET = IO1SET | LED0_bm;
}

void LedOn(unsigned char ucLedIndeks)
{
	switch(ucLedIndeks)
	{
		case 0:
			IO1SET |= LED0_bm;
			break;
		case 1:
			IO1SET |= LED1_bm;
			break;
		case 2:
			IO1SET |= LED2_bm;
			break;
		case 3:
			IO1SET |= LED3_bm;
			break;
	}
}


int main()
{
	unsigned char ucLedNumber = 0;
	
	LedInit();
	
	while(1)
	{
		LedOn(ucLedNumber % 4);
		Delay(250);
		IO1CLR |= (1<<(16 + (ucLedNumber % 4)));
		ucLedNumber++;																													//po przekroczeniu zakresu ucLedNumber jest ok
	}
}
//4.14
