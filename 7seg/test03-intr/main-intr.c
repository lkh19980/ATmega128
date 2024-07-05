/*
 * test03-intr.c
 *
 * Created: 2024-03-27 오후 12:25:30
 * Author : SYSTEM-00
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000L
#include <util/delay.h>

#define __delay_t 500
#define OPMODE_MAX		3
#define STATE_MAX	3

extern char* Disp(unsigned long num);

volatile int opmode = 0;
volatile int state = 0;


int main(void)
{
	
	// 7-Segment 사용 : 4 Module - C type
	// Pin assign : PDx - Segment img, PD0~3 - module select
	DDRD = 0xff;
	DDRE |= 0x0f;
	// Interrupt 사용 : INT4 ~ INT6 (Ext Int)
	// Pin assign : PE4 ~ PE6
	// 인터럽트 설정
    EIMSK = 0x70;// 0111 0000b
	EICRB = 0b00101010;
	SREG |= 0x80;//status Register - 인터럽트 허용
	sei();// set interrupt - 인터럽트 시작
	
	unsigned long t= 0;
	//reset();
    while (1) 
    {
		//PORTD = digit[0];
		//PORTE &= 0xf0;
		
		switch(opmode)
		{
			case 0: // reset
				t=0; 
				break;
			case 1: // counter start
				t++;
				break;
			case 2: // count stop
				break;
			default:
				break;
		}
		//Disp(65535);
		Disp(t);
		//Disp(t++);
    }
}

ISR(INT4_vect)
{
	opmode++;
	if(opmode>=OPMODE_MAX)opmode = 0;
}
ISR(INT5_vect)
{
	//PORTD = digit[0];
	//PORTE = 0x0c0;
	state++;
	if(state >= STATE_MAX) state = 0;
}
ISR(INT6_vect)
{
	
}