#include <LPC21xx.H>
#include "timer1_interrupts.h"

// TIMER
#define mCOUNTER_ENABLE 0x00000001
#define mCOUNTER_RESET  0x00000002

// CompareMatch
#define mINTERRUPT_ON_MR0 0x00000001
#define mRESET_ON_MR0     0x00000002
#define mMR0_INTERRUPT    0x00000001

// VIC (Vector Interrupt Controller) VICIntEnable
#define VIC_TIMER1_CHANNEL_NR 5

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE 0x00000020


void (*ptrTimer1InterruptFunction)(void);


/**********************************************/
//(Interrupt Service Routine) of Timer 1 interrupt
__irq void Timer1IRQHandler()
{
	T1IR=mMR0_INTERRUPT; 					// skasowanie flagi przerwania 
	ptrTimer1InterruptFunction();			// cos do roboty
	VICVectAddr=0x00; 						// potwierdzenie wykonania procedury obslugi przerwania
}

/**********************************************/


void Timer1Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void))		// microseconds
{ 
	ptrTimer1InterruptFunction = ptrInterruptFunction;

        // interrupts

	VICIntEnable |= (0x1 << VIC_TIMER1_CHANNEL_NR);            		// Enable Timer 1 interrupt channel 
	VICVectCntl2  = mIRQ_SLOT_ENABLE | VIC_TIMER1_CHANNEL_NR;  		// Enable Slot 0 and assign it to Timer 0 interrupt channel
	VICVectAddr2  =(unsigned long)Timer1IRQHandler; 	   			// Set to Slot 0 Address of Interrupt Service Routine 

        // match module

	T1MR0 = 15 * uiPeriod;                 	     			 		// value 
	T1MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0); 					// action 

        // timer

	T1TCR |=  mCOUNTER_ENABLE; // start 

}
