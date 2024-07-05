/*
 * test01.c
 *
 * Created: 2024-03-20 오전 11:42:04
 * Author : SYSTEM-00
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
//#include <util/delay.h>
#include <avr/delay.h>
const int __delay_t = 500;

void TogglePinA(int n,int delay) //n : n번째 비트 0-7, delay in ms
{
	char b = 1 <<n;
	PORTA |= b;
	_delay_ms(500);
	PORTA &= ~b;// PORTA의 0번째 비트를 LOW로 출력
	_delay_ms(500);
}

void LED(char* p,int n) //n : n번째 비트 0-7, delay in ms
{
	char b = 1 <<n;
	*p= b;
	_delay_ms(500);
	*p &= ~b;// PORTA의 0번째 비트를 LOW로 출력
	_delay_ms(500);
}
//LED(PORTD,0);

int main(void)
{
	//DDRA=0xFF;// A Port의 0번째 비트를 출력으로 사용, 나머지는 입력
	//|= 0이면 원래 값 1이면 무조건 1
	//&= 0이면 무조건 0 1이면 원래 값
	//DDRA |=0x01;
	//DDRA |=0x02;
	DDRA |= 0x07; //0b0000_0111 7
	//DDRA = 1<<DDRA4;
	DDRB &= 0xFE;//~0x01;
    /* Replace with your application code */
	
	
/*
//     while (1) 
//     {
// 		//PORTA |= 0b00000001;// PORTA의 0번째 비트를 HIGH로 출력
// 		//PORTA |= 0x02;
// 		//PORTA |= 0x03;
// 		/ *
// 		PORTA =0x01;
// 		_delay_ms(100);
// 		PORTA &= ~0x01;// PORTA의 0번째 비트를 LOW로 출력
// 		PORTA =0x02;
// 		_delay_ms(100);
// 		PORTA &= ~(0x02);
// 		PORTA =0x04;
// 		_delay_ms(100);
// 		PORTA &=~0x04;
// 		* /
// 	}
*/
/*
//     }
// 	while (1) 
//     {
// 		//if(PINB&0x01 == 1)	// switch pulled 1(pull up ckt)
// 		/ *
// 		if(!(PINB & 0x01 ==1))	// switch pushed 1
// 		{	
// 			TogglePinA(0,__delay_t);
// 			TogglePinA(1,__delay_t);
// 			TogglePinA(2,__delay_t);
// 		}
// 		* /
//     }
*/
/*
// 	while (1) 
//     {
// 		
// 		int count = 0;
// 		if(!(PINB&0x01 ==1))count +=1;// normal 1 pushed 0
// 		//if(PINB|0x01 == 0)count +=1;
// 		_delay_ms(20);
// 		if(count%3 == 0)	// switch pushed 1
// 		{
// 			TogglePinA(0,__delay_t);
// 		}
// 		if(count%3 == 1)	// switch pushed 1
// 		{
// 			
// 			TogglePinA(1,__delay_t);
// 			
// 		}
// 		if(count%3 == 2)	// switch pushed 1
// 		{
// 			TogglePinA(2,__delay_t);
// 		}
// 		
//     }
*/
	int mode = 0;
	while(1)
	{
		//if(PINB & 0x01 == 1) // SW 안눌리면 true
		if(!(PINB & 0x01 == 1))// SW 눌리면 True
		{
			mode++;
			if(mode >= 3) mode = 0;
		}
		//mode cannot be 0?
		switch(mode)
		{
			case 0:
			TogglePinA(0,__delay_t);
			break;
			case 1:
			TogglePinA(1,__delay_t);
			break;
			case 2:
			TogglePinA(2,__delay_t);
			break;
			default:
			mode = 0;
			break;
		}
	}
}

