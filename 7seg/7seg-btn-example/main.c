/*
 * 7seg-btn-example.c
 *
 * Created: 2024-03-22 오후 12:45:48
 * Author : SYSTEM-00
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>


uint8_t digit[]
= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x79,0x71,0xc0,0x00};

char arr[5];//세그먼트 이미지 정보를 담을 안전영역

void LED(char* p,int n) //n : n번째 비트 0-7, delay in ms
{
	char b = 1 <<n;
	*p= b;
	_delay_ms(500);
	*p &= ~b;// PORTA의 0번째 비트를 LOW로 출력
	_delay_ms(500);
}
//LED(PORTD,0);

void seg(int sel, uint8_t c)
{
	int i = 0;
	PORTE |= 0x0f;
	//PORTE &= ~(1<<(3-sel));
	PORTE &= ~(1<<sel);
	PORTD = c;
	_delay_ms(5);
	//PORTE |= 0x0f;
	//_delay_ms(100);
	
}

void FND_4(char *inf) // segment Image 배열
{
	for(int i = 0; i< 4 ; i++)
	{
		seg(i, *(inf+i));
	}
	
}
//문자열 고려서 안전영역 고려
//정적변수 영역에 부여
char* Trans(unsigned long num)//10진수 정수 ==> 16진수 문자열로 변환 : 65535 ==> 0xFFFF, 56506 ==> 0xDCBA
{								//16비트 세그문트 이미지 배열
	int n1 = num%0x10;			//A 1		:문자가 아닌 숫자
	int n2 = (num/0x10)%16;		//B 16		:
	int n3 = (num/0x100)%16;	//C 256
	int n4 = num/0x1000;		//D 4096	
	if(!(num/0x1000))
	{
		n4=17;
		if(!(num/0x100))
		{
			n3=17;
			if(!(num/0x10))n2=17;
		}
	}
	arr[0] = digit[n1];//char 1byte cast() LED문자로 표현
	arr[1] = digit[n2];
	arr[2] = digit[n3];
	arr[3] = digit[n4];
	//+, - 빠름
	//* 실수 연산 여러 클럭 사용
	//'/' 연산 여러 클럭 사용
	//FND_4(arr);
	return arr;
	
}

void reset()
{
	int i = 0;
	PORTE = 0x00;
	//PORTE &= ~(1<<i);
	PORTD = digit[16];
}

int main(void)
{
	
	int i=0;
	unsigned long j =0;
    //DDRD = 0x07;
	DDRD = 0xff;
	DDRE = 0x0f;
	
	DDRB &= ~0x01;
	int start = 0;//0 stop 1 start 2 pause
	reset();
    while (1) 
    {
		if(!(PINB & 1) )
		{
			_delay_ms(200);
			switch(start)
			{
				case 0:
				start = 1;
				break;
				case 1:
				start = 2;
				break;
				case 2:
				reset();
				start = 0;
				j = 0;
				break;
			}
		}
		
		
		
		
		
		switch(start)
		{
			case 1:
			
			FND_4(Trans(j++));
			_delay_ms(1);
			
			if(j>=0x10000)j = 0;
			break;
			
			case 2:
			FND_4(arr);
			break;
			
			default:
			start = 0;
			//reset();
			break;
		}
		
    }
	return 0;
}

