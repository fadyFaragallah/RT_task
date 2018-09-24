#include "GPIO/GPIO.h"
#include "ADC/ADC.h"
#include <avr/interrupt.h>
#include "Data_Types.h"

u16 voltage_reading;

ISR(ADC_vect)
{
	voltage_reading = myADCL | (myADCH<<8);
	
	GPIO_u8_WritePortVal(((voltage_reading/1023.0)*5),'d');
	myADCSRA|= (1<<6);
}
int main(void)
{
	GPIO_voidInit();
	GPIO_u8_WritePortDir(0x0F,'d');
	GPIO_u8_WritePinDir(0,0,'a');
	sei();
	ADC_voidInit();
	ADC_startConversion();
    while(1)
    {
        
    }
}