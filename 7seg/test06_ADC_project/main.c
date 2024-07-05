/*
 * test_06_ADC_project.c
 *
 * Created: 2024-05-31 오후 4:11:44
 * Author : user
 */ 

#include <avr/io.h>
#include "myHeader.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void SegPort(char *p1, char *p2);

void ADC_init(unsigned char channel)
{
	ADMUX = 0b11000000;
	
	ADCSRA |= 0x07;
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADFR);
	
	ADMUX  &=0b11000000;
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
	EIMSK = 0x70;
	EICRB = 0b00101010;
	SegPort(&PORTD, &PORTE);
	SREG |= 0x80;
	sei(); //set interrupt
	unsigned int read;
	
	while (1)
	{
		read = read_ADC();
		PORTF = read;
		SegDisp(read);
		_delay_ms(10);
	}
	return 0;
}

