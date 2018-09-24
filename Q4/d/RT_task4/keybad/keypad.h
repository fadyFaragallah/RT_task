
#ifndef KEYPAD_KEYPAD_H_
#define KEYPAD_KEYPAD_H_

#include <avr/io.h>
#include<util/delay.h>



//Keypad Information
#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6

#define keypadPORT PORTC
#define keypadPIN PINC
#define keypadDDR DDRC


//Keypad functions and global variables



void  Keypad_init();
char Keypad_getkey();

#endif /* KEYPAD_KEYPAD_H_ */
