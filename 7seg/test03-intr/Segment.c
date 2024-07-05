/*
 * Segment.c
 *
 * Created: 2024-03-28 오전 10:45:53
 *  Author: SYSTEM-00
 */ 

#include <avr/io.h>
//#include <avr/interrupt.h>
#include "..\test04-Timer\myHeader.h"
//#define F_CPU 16000000L
#include <util/delay.h>


uint8_t digit[]
= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x79,0x71,0xc0,0x00};
char arr[5];// 세그먼트 이미지 정보를 담을 영역


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
char* Disp(unsigned long num)//10진수 정수 ==> 16진수 문자열로 변환 : 65535 ==> 0xFFFF, 56506 ==> 0xDCBA
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
	FND_4(arr);
	//return arr;
	
}

void reset()
{
	int i = 0;
	PORTE = 0x00;
	//PORTE &= ~(1<<i);
	PORTD = digit[16];
}

