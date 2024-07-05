/*
 * test04-Timer-kitchen.c
 *
 * Created: 2024-03-28 오후 4:43:17
 * Author : SYSTEM-00
 */ 

#include <avr/io.h>
#include "myHeader.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void SegPort(char *p1, char *p2);

unsigned long cnt = 0, tcnt = 0;


#define OPMODE_MAX		3
#define STATE_MAX	3
volatile int opmode = 0;
volatile int state = 0;

unsigned long t= 0;

int main(void)
{
    /* Replace with your application code */
	SegPort(&PORTD, &PORTE);
	TIMSK |= 0x04;
	TCCR1B = 0x04;
	
	EIMSK = 0x70;// 0111 0000b
	EICRB = 0b00101010;
	
	
	
	SREG |= 0x80;
	sei(); //set interrupt
    while (1) 
    {
		if(cnt>= 0x10000)cnt = 0;
		SegDisp(t);
		switch(opmode)
		{
			case 0: // reset
				t=0; 
				break;
			case 1: // counter start
				
				t--;
				if (t==-1) opmode = 0;
				if(t == 0) opmode=4;
				break;
			case 2: // count stop
				break;
			case 3:
				t++;
				if(t>=10000)opmode = 0;
				break;
			case 4:
			//LED
			PORTA = 0x0f;
			_delay_ms(50);
			PORTA = 0x00;
			_delay_ms(50);
			PORTA = 0x0f;
			_delay_ms(50);
			PORTA = 0x00;
			_delay_ms(50);
			/*
			Disp(t);
			_delay_ms(15);
			Disp(t);
			_delay_ms(15);
			Disp(t);
			_delay_ms(15);
			Disp(t);
			_delay_ms(15);
			*/
			break;
			default:
				break;
		}
    }
	
}
ISR(TIMER1_OVF_vect)//interrupt service routine // interrupt vector
{
	cnt++;
}
ISR(INT4_vect)
{
	opmode++;//
	if(opmode == 5)opmode =0;
	if(opmode>=OPMODE_MAX)opmode = 1; //1,2
	
}
ISR(INT5_vect)
{
	//PORTD = digit[0];
	//PORTE = 0x0c0;
	state++;
	if(state >= 2) state = 0;
	opmode = state+2;
	//opmode++;//
	//if(opmode>=4)opmode = 2;
}
ISR(INT6_vect)
{
	opmode = 0;
}