#'#'추가
```
/*
 * 7seg-btn.c
 *
 * Created: 2024-03-22 오전 9:49:43
 * Author : SYSTEM-00
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
uint8_t numbers[]
= {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x77,0x7c,0x58,0x5e,0x79,0x71,0xc0,0x00};

void display(int *d)
{
	int i = 0;
	for(i = 0; i<4 ; i++)
	{
		PORTE |= 0x0f;
		PORTE &= ~(1<<i);
		PORTD = numbers[d[i]];
		_delay_ms(5);
	}
}




void reset()
{
	int i = 0;
	PORTE = 0x00;
	//PORTE &= ~(1<<i);
	PORTD = numbers[16];
}
//PORTE에 0이 출력 1이 출력 안함

int main(void)
{
	
	DDRD = 0xff;//세그먼트 제어 핀 8개를 출력으로 설정
	DDRE = 0x0f;//자릿수 전택 핀 4개를 출력으로 설정
	DDRB &= ~0x01;
    /* Replace with your application code */
	//PORTD -> *PORTD 포인터로 넘기기
	int i=0,j=0,count = 0;
	int start = 0;//0 stop 1 start 2 pause
	int d[4] = {0,0,0,0};
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
				count = 0;
				break;
			}
		}
		
		
		
		switch(start)
		{
			case 1:
			/*
			if(count/16)
			{
				PORTE|= 0x0f;
				PORTE &= ~(1<<(count/16));
			}
			PORTD = numbers[count++%16];
			*/
			
			///*	
			d[0] = count%10;
			d[1] = (count%100)/10;
			d[2] = (count%1000)/100;
			d[3] = count/1000;//count max 9999
			
			if(!(count/1000))
			{
				d[3]=17;
				if(!(count/100))
				{
					d[2]=17;
					if(!(count/10))d[1]=17;
				}
			}
			//*/
			/*
			d[0]=0;
			d[1]=1;
			d[2]=5;
			d[3]=3;
			*/
			display(d);
			//_delay_ms(200);
			count ++;
			if(count>=10000)count = 0;
			break;
			
			case 2:
			display(d);
			break;
			
			default:
			start = 0;
			reset();
			break;
		}
		
		
    }
}
```
