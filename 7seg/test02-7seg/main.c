/*
 * test02-7seg.c
 *
 * Created: 2024-03-21 오후 3:34:04
 * Author : SYSTEM-00
 */ 

#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	uint8_t numbers[]
		= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x79,0x71,0xc0};
	int i, j;
	
	DDRD = 0xff;//세그먼트 제어 핀 8개를 출력으로 설정
	DDRE = 0x0f;//자릿수 전택 핀 4개를 출력으로 설정
    while (1) 
    {
		for (i = 0; i<4 ; i++)
		{
			//PORTE |= 0x0f;
			//PORTE &= (1<<i);
			PORTE |= (0x0f);//해당 자리에만 GND로 연결 나머지는 1을 출력해서 자리 선택
			PORTE &= ~(1 << i);
			
			for (j = 0; j < 16; j++){
				PORTD = numbers[j];//데이터 출력
				_delay_ms(200);//0.2초 간격 전환
			}
		}
    }
}

