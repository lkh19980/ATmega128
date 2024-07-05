/*
 * 7seg.c
 *
 * Created: 2024-03-21 오후 2:36:41
 * Author : SYSTEM-00
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
const int __delay_t = 500;

int main(void)
{
	DDRD = 0xff;
	DDRE = 0x0f;
    /* Replace with your application code */
	PORTE = 0x0f;
    while (1) 
    {
		//PORTD = 0x01;
 		//_delay_ms(500);
		// /*
 		PORTD = ~0x3f;//0
 		_delay_ms(500);
 		PORTD = ~0x06;
 		_delay_ms(500);
 		PORTD = ~0x5b;
 		_delay_ms(500);
 		PORTD = ~0x4f;
 		_delay_ms(500);
 		PORTD = ~0x66;
 		_delay_ms(500);
 		PORTD = ~0x6d;
 		_delay_ms(500);
 		PORTD = ~0x7d;//6
 		_delay_ms(500);
 		PORTD = ~0x27;
 		_delay_ms(500);
 		PORTD = ~0x7f;
 		_delay_ms(500);
 		PORTD = ~0x6f;
 		_delay_ms(500);
		 //*/
		PORTD = ~0x77;
		_delay_ms(500);
		PORTD = ~0x7c;
		_delay_ms(500);
		PORTD = ~0x39;
		_delay_ms(500);
		PORTD = ~0x5e;
		_delay_ms(500);
		PORTD = ~0x79;
		_delay_ms(500);
		PORTD = ~0x71;
		_delay_ms(500);
    }
}

