#include <LPC21xx.H>

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)
#define BUTTON0_bm (1<<4)
#define BUTTON1_bm (1<<6)
#define BUTTON2_bm (1<<5)
#define BUTTON3_bm (1<<7)




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

unsigned char ReadButton1()
{
    if((IO0PIN & BUTTON0_bm) == 0)
    {
        return 1;
    }
    else    
    {
        return 0;
	}
}


int main()
{	
	LedInit();
	
	while(1)
	{
		if(ReadButton1() == 1)	
		{
			IO1SET |= LED1_bm;
            IO1CLR |= LED0_bm;
		}
		else
		{
			IO1SET |= LED0_bm;
            IO1CLR |= LED1_bm;
		}
	}
}
//4.16
