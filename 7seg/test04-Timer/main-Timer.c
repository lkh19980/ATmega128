/*
 * test04-Timer.c
 *
 * Created: 2024-03-28 오전 10:57:06
 * Author : SYSTEM-00
 */ 
#include "myHeader.h"
//#include "../test03-intr/segment.c"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define __delay_t 500

void SegPort(char *p1, char *p2);

unsigned long cnt = 0, tcnt = 0;

int main(void)
{
	//DDRD = 0xff; //DATA DIRECTION REGISTER
	//DDRE |= 0x0f;
	SegPort(&PORTD, &PORTE);
	
//  TIMSK |= 0x01; // 0000 0001b - Timer 0 TCNT overflow interrupt
	TIMSK |= 0x04; // 0000 0001b - Timer 1 TCNT overflow interrupt (16bit)
	//TIMSK |= 0x40; // 0000 0001b - Timer 2 TCNT overflow interrupt
	
//	TCCR0 = 0x04; //분주비 (Pre-Scaler) 64
	TCCR1B = 0x04;
	//TCCR2 = 0x04;
	SREG |= 0x80;
    sei();
	while (1) 
    {
		
		if(cnt>= 0x10000)cnt = 0;
		SegDisp(cnt);
    }
}

ISR(TIMER1_OVF_vect)
{
	cnt++;
	
	
}

// ISR(TIMER2_OVF_vect)
// {
// 	tcnt++;
// 	if(tcnt>1000)
// 	{
// 		cnt++, tcnt = 0;
// 	}
//
// }

// ISR(TIMER0_OVF_vect)
// {
// 	tcnt++;
// 	if(tcnt>1000)
// 	{
// 		cnt++, tcnt = 0;
// 	}
// 	
// }

