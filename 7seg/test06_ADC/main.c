/*
 * test06_ADC.c
 *
 * Created: 2024-05-31 오후 4:35:58
 * Author : user
 */ 

#include <avr/io.h>
#include "myHeader.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void SegPort(char *p1, char *p2);

void ADC_init(unsigned char channel)
{
	ADMUX |= (1 << REFS0);
	
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADFR);
	
	ADMUX  |= (ADMUX & 0xE0); //&=0b11100000;
	ADCSRA |= (1 << ADSC);
}

int read_ADC(void)
{
	while(!(ADCSRA & (1 << ADIF)));
	
	return ADC;
}
int main(void)
{
	/* Replace with your application code */
	DDRD = 0xff;
	DDRE = 0x0f;
	DDRF = 0x00;
	DDRF = 0x04;
	
	ADC_init(0);
	
	EIMSK = 0x70;
	EICRB = 0b00101010;
	SegPort(&PORTD, &PORTE);
	SREG |= 0x80;
	sei(); //set interrupt
	unsigned int read;
	
	while (1)
	{
		read = read_ADC();
		//PORTF = read;
		SegDisp(read);
		_delay_ms(5);
	}
	return 0;
}

