/*
 * Segment.c
 *
 * Created: 2024-03-28 오전 10:45:53
 *  Author: SYSTEM-00
 */ 

#include <avr/io.h>
//#include <avr/interrupt.h>
#include "..\test04-Timer\myHeader.h"
// #include "myHeader2.h"
//#define F_CPU 16000000L
#include <util/delay.h>


uint8_t digit[]
= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x79,0x71,0xc0,0x00};
char arr[5];// 세그먼트 이미지 정보를 담을 영역
volatile unsigned char *PA = &PORTD, *PB = &PORTE;
//int sm = 4;
int select = 4;//0~3 선택시 깜빡임 초기 4
int count = 0;
void SegPort(char *p1, char *p2)
{
	PA = p1; PB = p2;//*PA는 포트 출력 작업이 됨
}
void seg(int sel, uint8_t c)
{
	//int i = 0;
	*PB |= 0x0f;
	//PORTE &= ~(1<<(3-sel));
	*PB &= ~(1<<sel);
	*PA = c;
	_delay_ms(5);
	//PORTE |= 0x0f;
	//_delay_ms(100);
	
}

void FND_4(char *inf) // segment Image 배열
{
	//for(int i = 0; i< sm ; i++)
	for(int i = 0; i< 4 ; i++)
	{
		if (select == i)//해당 자릿수가 되었을 때
		{
			if((count++/30)%2)//100이 넘으면
			{
				//count = 0;//초기화
				seg(i, *(inf+i));//출력
				if(count>10000) count = 0;
			}
			continue;	//100 안넘으면 넘기기
		}
		seg(i, *(inf+i));
	}
	
}
//문자열 고려서 안전영역 고려
//정적변수 영역에 부여
char* SegDisp(unsigned long num)//10진수 정수 ==> 16진수 문자열로 변환 : 65535 ==> 0xFFFF, 56506 ==> 0xDCBA
{								//16비트 세그문트 이미지 배열
// 	DDRD |= 0xff;
// 	DDRE |= 0x0f;
	num %= 6000;
	int n1 = num%10;			//A 초에 대해서 10의 나머지
	int n2 = (num%60)/10;		//B 초에 대해서 60으로 나눈 나머지의 10의 자릿수
	int n3 = (num/60)%10;		//C 60으로 나눠 분을 만든 것의 1의 자리수
	int n4 = (num/60)/10;		//D 60으로 나눠 분으 만든 것의 10의 자릿수
	/*
	if(!(num/1000))
	{
		n4=17;
		if(!(num/100))
		{
			n3=17;
			if(!(num/10))n2=17;
		}
	}
	sm=(num>999) ? 4 : (num > 99) ? 3: (num> 9) ? 2: 1;
	*/
	arr[0] = digit[n1];//char 1byte cast() LED문자로 표현
	arr[1] = digit[n2];
	arr[2] = digit[n3] | 0x80;
	arr[3] = digit[n4];
	//+, - 빠름
	//* 실수 연산 여러 클럭 사용
	//'/' 연산 여러 클럭 사용
	FND_4(arr);
	return arr;
	
}

void reset()
{
	//int i = 0;
	PORTE = 0x00;
	//PORTE &= ~(1<<i);
	PORTD = digit[16];
}

