#include <LPC21xx.H>

#define PINSEL_ADC_P0_27 	(1<<22)
#define ADC_SEL_AIN0 		(1<<0)
#define ADC_CLKDIV_PRESC 	(14<<8)
#define ADC_PDN_BIT 		(1<<21)
#define ADC_CONV_DONE_BIT 	(1<<31)
#define ADC_CONV_DATA		0x0000FFC0
#define ADC_START_CONV 		(1<<24)



void ADCInit(void)
{
	PINSEL1 |= PINSEL_ADC_P0_27;	//set alternative function of pin P0.27 to Analog in
	ADCR |= ADC_SEL_AIN0;			//set active AIN0 pin 
	ADCR |= ADC_CLKDIV_PRESC;		//set clock to 4MHz
	ADCR |= ADC_PDN_BIT;			//set adc to operational mode
}


unsigned int ADCStartConversion(void)
{
	ADCR |= ADC_START_CONV;						//start conversion
	while((ADDR & ADC_CONV_DONE_BIT) == 0){}
	return ((ADDR & ADC_CONV_DATA) >> 6);
}
