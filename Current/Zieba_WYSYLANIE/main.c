#include "timer_interrupts.h"
#include "uart.h"
#include "string.h"

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
	char acStringToSend[15]; 
	
	UART_InitWithInt(9600);
	Timer0Interrupts_Init(1000000, &WatchUpdate);
	
	while(1)
	{
		if(FREE == eTransmiter_GetStatus())
		{
			if(1 == sWatch.fSeccondsValueChanged)
			{
				CopyString("sec ", acStringToSend);
				AppendUIntToString(sWatch.ucSecconds, acStringToSend);
				sWatch.fSeccondsValueChanged = 0;
				
				AppendString("\n\r", acStringToSend);
				Transmiter_SendString(acStringToSend);
			}
			else if(1 == sWatch.fMinutesValueChanged) 					//else zeby nie sprawdzac drugi raz statusu transmitera
			{
				CopyString("min ", acStringToSend);
				AppendUIntToString(sWatch.ucMinutes, acStringToSend);
				sWatch.fMinutesValueChanged = 0;
				
				AppendString("\n\r", acStringToSend);
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
