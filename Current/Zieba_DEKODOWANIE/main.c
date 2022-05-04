#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"


/*******************************************/
int main()
{	
	char acRecievedString[RECIEVER_SIZE];
	
	UART_InitWithInt(9600);
	//KeyboardInit();
	ServoInit(50);
	

	while(1)
	{		
		if(READY == eReciever_GetStatus())
		{
			Reciever_GetStringCopy(acRecievedString);
			DecodeMsg(acRecievedString);
			
			if((ucTokenNr > 0) && (KEYWORD == asToken[0].eType))
			{
				switch(asToken[0].uValue.eKeyword)
				{
					case CAL:
						ServoCallib();
						break;
					
					case GT:
						if((NUMBER == asToken[1].eType) && ucTokenNr > 1)
						{
							ServoGoTo(asToken[1].uValue.uiNumber);
						}
						break;
				}
			}
		}
	}
}
/*******************************************/
