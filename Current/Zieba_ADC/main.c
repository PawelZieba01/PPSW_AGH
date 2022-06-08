#include "timer1_interrupts.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"
#include "servo.h"

void WatchUpdate(void);

struct Watch
{
	unsigned char ucMinutes; 
	unsigned char ucSecconds; 
	unsigned char fSeccondsValueChanged; 
	unsigned char fMinutesValueChanged;
};

struct Watch sWatch;

/*******************************************/
int main()
{	
	unsigned char fCalcCommandRecieved = 0;
	unsigned char fIdCommandRecieved = 0;
	unsigned char fUnknownCommandRecieved = 0;
	unsigned int uiCalcValue;
	
	char acStringToSend[16]; 
	char acRecievedString[16];
	
	UART_InitWithInt(9600);
	ServoInit(50);
	Timer1Interrupts_Init(1000000, &WatchUpdate);
	
	while(1)
	{
		if(READY == eReciever_GetStatus())
		{
			Reciever_GetStringCopy(acRecievedString);
			
			DecodeMsg(acRecievedString);
			
			if((ucTokenNr > 0) && (KEYWORD == asToken[0].eType))
			{
				if(CALC == asToken[0].uValue.eKeyword)
				{
					fCalcCommandRecieved = 1;
					uiCalcValue = asToken[1].uValue.uiNumber * 2;
				}
				
				if(ID == asToken[0].uValue.eKeyword)
				{
					fIdCommandRecieved = 1;
				}
				
				if(GOTO == asToken[0].uValue.eKeyword)
				{
					ServoGoTo(asToken[1].uValue.uiNumber);
				}
				
				if(CALLIB == asToken[0].uValue.eKeyword)
				{
					ServoCallib();
				}
			}
			else
			{
				fUnknownCommandRecieved = 1;
			}
		}

		
		if(FREE == eTransmiter_GetStatus())
		{
			if (1 == fCalcCommandRecieved)
			{
				fCalcCommandRecieved = 0;
				CopyString("calc ", acStringToSend);
				AppendUIntToString(uiCalcValue, acStringToSend);
				
				AppendString("\n\r", acStringToSend);
				Transmiter_SendString(acStringToSend);
			}
			else if(1 == sWatch.fSeccondsValueChanged)
			{
				sWatch.fSeccondsValueChanged = 0;
				CopyString("sec ", acStringToSend);
				AppendUIntToString(sWatch.ucSecconds, acStringToSend);
				
				AppendString("\n\r", acStringToSend);
				Transmiter_SendString(acStringToSend);
			}
			else if(1 == sWatch.fMinutesValueChanged) 					//else zeby nie sprawdzac drugi raz statusu transmitera
			{
				sWatch.fMinutesValueChanged = 0;
				CopyString("min ", acStringToSend);
				AppendUIntToString(sWatch.ucMinutes, acStringToSend);
				
				AppendString("\n\r", acStringToSend);
				Transmiter_SendString(acStringToSend);
			}
			else if(1 == fIdCommandRecieved) 
			{
				fIdCommandRecieved = 0;
				CopyString("ID: LPC_2129/01\n\r", acStringToSend);
				
				Transmiter_SendString(acStringToSend);
			}
			else if(1 == fUnknownCommandRecieved) 
			{
				fUnknownCommandRecieved = 0;
				CopyString("UNKNOWN COMMAND\n\r", acStringToSend);
				
				Transmiter_SendString(acStringToSend);
			}
		}
	}
}
/*******************************************/

void WatchUpdate(void)
{
	sWatch.ucSecconds++;
	sWatch.fSeccondsValueChanged = 1;
	
	if(sWatch.ucSecconds >= 60)
	{
		sWatch.ucSecconds = 0;
		sWatch.ucMinutes++;
		sWatch.fMinutesValueChanged = 1;
	}
	
	if(sWatch.ucMinutes >= 60){
		sWatch.ucMinutes=0;
	}
}
