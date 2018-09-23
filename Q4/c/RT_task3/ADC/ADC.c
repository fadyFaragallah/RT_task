#include "ADC.h"


void ADC_voidInit()
{
	myADCSRA = 0X8F;
	myADMUX = 0X40;
}

void ADC_startConversion()
{
	myADCSRA|= (1<<6);
}