/*
 * test06-UART.c
 *
 * Created: 2024-06-07 오전 10:36:23
 * Author : user
 */ 

#include <avr/io.h>
//#include <xc.h>
#include <stdio.h>
#include <util/delay.h>

#include <avr/interrupt.h>

#define F_CPU 16000000L;

void initUART0()
{
	UBRR0H = 0;
	UBRR0L = 207; // Baud rate : 9600;
	UCSR0A |= (1<<U2X0);
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= 0x06; // Data bit : 8 x11x 00000110 COM3 9600 N81
					// Stop bit : 1 0xxx
}

void uPutc(char c)
{
	while(!(UCSR0A & (1<<UDRE0)));
	/*
	while(1)
	{
		if(UCSR0A & (1 << UDRE0) == 1) break; // Wait until data empty bit test 1
	}
	*/
	UDR0 = c; // send
}

void uPuts(char *str)
{
	while(*str) uPutc(*str++);
	/*
	while(1)
	{
		if(*str == 0) break;
		uPutc(*str);
		str++;
	}
	*/
	//while(!(UCSR0A & (1<<UDRE0)));
	//UDR0 = *(str++);
	
}

unsigned char buf[1024];
void bPrint()
{
	uPuts(buf);
}

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
	DDRD = 0xff;
	DDRE = 0x0f;
	DDRF = 0x00;
	DDRF = 0x04;
	
	ADC_init(0);
	
	//EIMSK = 0x70;
	//EICRB = 0b00101010;
	
	//SREG |= 0x80;
	//sei(); //set interrupt
	unsigned int read;
	
	
    /* Replace with your application code */
	initUART0();
	char a = '0';
	uPuts("\r\n 안녕하세요....^^. \r\n");
	//printf => print format
	//sprintf => string printf
	//fprintf => file printf
	unsigned char percent = 0;
	int i = 0;
	UCSR0B &= !(1 << TXEN0);
	while (1) 
	{
		if(!(PINE & 0x10))
		{
			uPuts("PINE4 == 1\r\n");
			if(UCSR0B & (1 << TXEN0))
			{
				UCSR0B &= !(1 << TXEN0);
				_delay_ms(600);
			}
			else
			{
				UCSR0B |= (1 << TXEN0);
				_delay_ms(600);
			}
		}else
		{
		//send(a++);
		//uPutc(a++);
		//sprintf(buf,"\r\nATmega128 터미널 출력 테스트 ... #%d virus uploading : %d%%\r\n",i++, percent++); bPrint();
		//uPuts(buf);
		read=read_ADC();
		sprintf(buf,"ADC 값  출력 : %d \r\n",read); bPrint();
		_delay_ms(500);
		//if(a > '9') a= '0';
		}
	}

}

