#include <avr/io.h>
#include <avr/interrupt.h>
#include "keybad/keypad.h"
#include "lcd/lcd.h"

#define CORRECT_PASSWORD "123"
#define CORRECT_PASSWORD_LENGTH 3

char* correctPassword = CORRECT_PASSWORD;
char enteredPassword[CORRECT_PASSWORD_LENGTH];
char running = 1;
char continueTakingPasswords = 1;
int trials = 0;
int inputIndex = 0;

void correctPasswordEntered();
void wrongPasswordEntered();
void init_GPIO();
void init_Timer0();
void timer0_ISR();
void getPassoword();
void enableTimer0();


ISR(INT0_vect)
{
	int i;
	unsigned char equals = 1;
	for(i = 0; i<CORRECT_PASSWORD_LENGTH; i++)
	{
		if(enteredPassword[i] != correctPassword[i])
		{
			equals = 0;
			break;	
		}
	}
	
	if(equals)
	{
		correctPasswordEntered();
	}
	
	else
	{
		wrongPasswordEntered();
	}
	
}

ISR(TIMER0_COMP_vect)
{
	//used to count exactly 4 * 250ms = 1 s
	static int quarter_second_counter = 0;

	quarter_second_counter++;
	
	if(quarter_second_counter==4) //every 3 seconds exactly
	{
		PORTD ^= (0b11 << 3);
		quarter_second_counter = 0;
	}
}


int main(void)
{
	
	LCD_lcd_init();
	Keypad_init();
	
	LCD_Send_A_String("Enter password");
	LCD_GotoXY(1,0);

	init_GPIO();
	init_Timer0();
	sei();

	getPassoword();

    while (running) 
    {		
			if(continueTakingPasswords)
			{	
				char inputChar = Keypad_getkey();
				if(inputChar == 'A') continue;
				enteredPassword[inputIndex] = inputChar;
				LCD_Send_A_Character(enteredPassword[inputIndex]);
				if(inputIndex == (CORRECT_PASSWORD_LENGTH - 1))
				inputIndex = 0;
				else
				inputIndex++;
			}
    }
}

void correctPasswordEntered()
{
	LCD_clear_screen();
	LCD_GotoXY(0,0);
	LCD_Send_A_String("Correct");
	LCD_GotoXY(1,0);
	PORTD |= 0b11;
	continueTakingPasswords = 0;
	
}


void wrongPasswordEntered()
{
	trials++;
	LCD_clear_screen();
	LCD_GotoXY(0,0);
	if(trials<3)
	LCD_Send_A_String("Wrong, Re-enter");
	else
	LCD_Send_A_String("Wrong!");
	LCD_GotoXY(1,0);
	
	if(trials<3)
	{	
		getPassoword();
	}
	
	else
	{
		continueTakingPasswords = 0;
		enableTimer0();
	}
}


void init_GPIO()
{	

	DDRD = 0b11011;
	PORTD |= 1<<2;
	SFIOR |= 1<<2;
	MCUCR |= 0b10;
	GICR |= 1<<6;
}

void getPassoword()
{
		inputIndex = 0;
}


void init_Timer0()
{
	//clear timer on compare mode
	TCCR0 &= ~(1<<WGM00);
	TCCR0 |= (1<<WGM01);
	
	//prescaling = 1024
	TCCR0 &= 0b000;
	
	//enable interrupt
	TIMSK |= 1<<OCIE0;
	OCR0 = 244;
}


void enableTimer0()
{
	TCCR0 |= 0b101;
}


