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
	IO1DIR |= LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	IO1SET |= LED0_bm;
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
		default:
			IO1CLR |= LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	}
}


enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum KeyboardState eKeyboardRead()
{
	unsigned char ucKeyboardBits = IO0PIN & 0xF0; 
	
		if((ucKeyboardBits & BUTTON0_bm) == 0) {return BUTTON_0;}
		else if((ucKeyboardBits & BUTTON1_bm) == 0) {return BUTTON_1;}	 
		else if((ucKeyboardBits & BUTTON2_bm) == 0) {return BUTTON_2;}
		else if((ucKeyboardBits & BUTTON3_bm) == 0) {return BUTTON_3;}
		else {return RELASED;}
}

void KeyboardInit()
{
	IO1DIR = IO1DIR & ~(BUTTON0_bm | BUTTON1_bm | BUTTON2_bm | BUTTON3_bm);
}



int main()
{	
	LedInit();
	KeyboardInit();
	
	while(1)
	{
		LedOn(4);
		switch(eKeyboardRead())
        {
            case RELASED:
				LedOn(4);
				break;
			
            case BUTTON_0:
				LedOn(0);
				break;
			
			case BUTTON_1:
				LedOn(1);
				break;
			
			case BUTTON_2:
				LedOn(2);
				break;
			
			case BUTTON_3:
				LedOn(3);
				break;
        }
	}
}
//4.19
