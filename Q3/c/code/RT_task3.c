#include "GPIO/GPIO.h"
#include "ADC/ADC.h"
#include <avr/interrupt.h>
#include "Data_Types.h"

u16 voltage_reading;

ISR(ADC_vect)
{
	voltage_reading = myADCL | (myADCH<<8);
	
	OCR0=((voltage_reading/1023.0)*255);
	myADCSRA|= (1<<6);
}
int main(void)
{
	GPIO_voidInit();
	GPIO_u8_WritePortDir(0x01,'d');
	GPIO_u8_WritePinDir(3,1,'b');
	sei();
	ADC_voidInit();
	TCCR0 = 0X69;
	ADC_startConversion();
	while(1)
	{
		
	}
}