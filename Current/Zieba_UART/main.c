#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "led.h"

#define NULL '\0'

extern struct RecieverBuffer sRxBuffer;

void Delay(unsigned int uiDelayMilliseconds);

/*******************************************/
int main()
{	
	//UART_InitWithInt(9600);
	//KeyboardInit();
	//ServoInit(50);
	
	Reciever_PutCharacterToBuffer ('k');
	Reciever_PutCharacterToBuffer ('o');
	Reciever_PutCharacterToBuffer ('d');
	Reciever_PutCharacterToBuffer (TERMINATOR);
	
	sRxBuffer.eStatus = EMPTY;
	Reciever_PutCharacterToBuffer ('k');
	Reciever_PutCharacterToBuffer ('o');
	Reciever_PutCharacterToBuffer ('d');
	Reciever_PutCharacterToBuffer ('1');
	Reciever_PutCharacterToBuffer (TERMINATOR);

	//while(1)
	//{
	//
	//}
}
/*******************************************/


/*void Delay(unsigned int uiDelayMilliseconds)
{
	unsigned int uiDelayCounter;
	
	for(; uiDelayMilliseconds > 0; uiDelayMilliseconds--)
	{
		for(uiDelayCounter = 0; uiDelayCounter < 7500; uiDelayCounter++){}
	}
}*/
