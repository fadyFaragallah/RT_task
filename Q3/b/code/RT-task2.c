#include "GPIO/GPIO.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#define STATE_NUMBERS 6
enum state{
	off1,
	off2,
	off,
	on,
	slow,
	fast
	};
	
enum state ledState[3]={off,off2,off1};
ISR(INT0_vect)
{
	for(int i=0;i<3;i++)
	{
		ledState[i]=(ledState[i]+1)%STATE_NUMBERS;
		if((ledState[i]==off)||(ledState[i]==off1)||(ledState[i]==off2))
			 {
				 GPIO_u8_WritePinVal(i,0,'a');
				 
			 }
		else if(ledState[i]==on) 
			{
				GPIO_u8_WritePinVal(i,1,'a');
				
			}
		else if(ledState[i]==fast)
		 {
			 TCCR0=0x04;
			 TIMSK|= 0x1;
		}
		else if(ledState[i]==slow)
		{
			TCCR2=0x01;
			TIMSK|=0x40;
		}
	}
}
ISR(TIMER0_OVF_vect)
{
	for(int i=0;i<3;i++)
	{
		if(ledState[i]==fast)
		{
			u8 *val;
			GPIO_u8_ReadPinVal(i,val,'a');
			GPIO_u8_WritePinVal(i,(*val)^0x1,'a');
			break;
		}
	}
}
ISR(TIMER2_OVF_vect)
{
	for(int i=0;i<3;i++)
	{
		if(ledState[i]==slow)
		{
			u8 *val;
			GPIO_u8_ReadPinVal(i,val,'a');
			GPIO_u8_WritePinVal(i,(*val)^0x1,'a');
			break;
		}
	}
}
int main(void)
{
	GPIO_voidInit();
	GPIO_u8_WritePortDir(0x07,'a');
	GPIO_u8_WritePinDir(2,0,'d');
	SREG|=0x80;
	MCUCR|=0x03;
	GICR|=0x40;
	
	TCCR0 = 0x00; //fast
	TCCR2 = 0x00; //slow
	
    while(1)
    {
       
    }
}