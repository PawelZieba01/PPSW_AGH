#include "servo.h"
#include "uart.h"
#include "strings.h"

#define RECIEVED_STRING_SIZE 254


/*******************************************/
int main()
{	
	char acRecievedString[RECIEVED_STRING_SIZE];
	
	UART_InitWithInt(9600);
	//KeyboardInit();
	ServoInit(50);
	

	while(1)
	{		
		if(READY == eReciever_GetStatus())
		{
			Reciever_GetStringCopy(acRecievedString);
			
			if(EQUAL == eCompareString(acRecievedString, "callib"))
			{
				ServoCallib();
			}
			else if(EQUAL == eCompareString(acRecievedString, "left"))
			{
				ServoGoTo(12);
			}
			else if(EQUAL == eCompareString(acRecievedString, "right"))
			{
				ServoGoTo(36);
			}
		}
	}
}
/*******************************************/
