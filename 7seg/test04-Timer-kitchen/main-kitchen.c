/*
 * test04-Timer-kitchen.c
 *
 * Created: 2024-03-28 오후 4:43:17
 * Author : SYSTEM-00
 */ 

#include <avr/io.h>
#include "myHeader.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void SegPort(char *p1, char *p2);

unsigned long cnt = 0, tcnt = 0;//타이머 카운터 실제 1초 측정


#define OPMODE_MAX		3
#define STATE_MAX	3
volatile int opmode = 0;//작동 모드
volatile int state = 0;//임의 상태

unsigned long time= 0;//설정 시간
int time_var=0;//변경 시간
unsigned long time_see = 0; //표시시간

int main(void)
{
    /* Replace with your application code */
	
	//LED PORT 허용
	DDRA |= 0x0f;
	DDRD |= 0xff;
	DDRE |= 0x0f;
	
	
	//LED출력 포트 지정
	SegPort(&PORTD, &PORTE);
	
	//타이머 설정
	TIMSK |= 0x04;
	TCCR1B |= 0x00;
	//TCCR1B |= 0x04;
	
	//외부 인터럽트 설정
	EIMSK |= 0x70;// 0111 0000b
	EICRB |= 0b00101010;
	
	
	
	SREG |= 0x80;
	sei();
	//cli();
    while (1) 
    {
		//기본 초 표현
		if(cnt>= 6000)cnt = 0;
		//SegDisp(cnt);
		
		switch(opmode)
		{
			case 0:
				cnt=0;
				DDRD |= 0xff;
				DDRE |= 0x0f;
				
				break;
			case 1:// 스톱워치
				time_see = cnt;
				//time = time_see;
				break;
			case 2: //시간 설정 모드
				
				switch(state)
				{
					case 4://십의 자리 초 입력 대기
					
					case 5://십의자리 초 입력 모드
						if(time_var>5)time_var=0;
						else if(time_var<0)time_var=5;
						break;
					default://나머지 모드 
						if(time_var<0)
						{
							time_var =9;
						}else if(time_var>9)
						{
							time_var = 0;
						}
						break;
				}
				
				
				switch(state)
				{
					case 0:
						//ISR5누를시 설정후 다음으로 넘어감
						time_see = time + time_var*600;
						break;
					case 1://input 3번째
						time += time_var*600;// 시간 입력
						select =2;//자릿수 변경
						time_var = 0;//시간 변경값 초기화
						state++;//다음 상태로 
						break;
					case 2:
						//ISR5누를시 설정후 다음으로 넘어감
						time_see = time + time_var*60;
						break;
					case 3://input 2번째
						time += time_var*60;//시간 입력
						select =1;//자릿수 변경
						time_var = 0;//시간 변경값 초기화
						state++;
						break;
					case 4:
						//ISR5누를시 설정후 다음으로 넘어감
						time_see = time + time_var*10;
						break;
					case 5://input 1번째
						time += time_var*10;
						select =0;
						time_var = 0;//시간 변경값 초기화
						state++;
						break;
					case 6:
						//ISR5누를시 설정후 다음으로 넘어감
						time_see = time + time_var;
						break;
					case 7://input 0번째
						time += time_var;
						state = 0; //초기 상태로 복귀
						select =4; //깜빡임 없엠
						time_var = 0;//시간 변경값 초기화
						time_see = time;
						opmode = 3; //타이머 시작 정지 모드로 변경
						break;
					default:
					break;
				}
				break;
			case 3://타이머 시간 감소 모드
				time_see = time-cnt;//반복문이라 time을 바로 빼면 반복되서 금방 0이 된다.
				
				if(!(time_see))
				{
					opmode=4;
				}
				break;
			case 4://타이머 종료
				TCCR1B = 0x00;
				cnt=0;
				PORTA=0x0f;
				//SegDisp(time_see);
				DDRD &=~(0xff);
				_delay_ms(100);
				PORTA=0x00;
				//SegDisp(time_see);
				DDRE &=~(0x0f);
				_delay_ms(100);
				break;
			default:
				break;
		}
		SegDisp(time_see);
	}
		
	
}
ISR(TIMER1_OVF_vect)
{
	cnt++;
}
ISR(INT4_vect)// 시작 정지 리셋 / 시간 설정시 업
{
	if(opmode == 0) //스탑워치로
	{
		opmode=1;
		cnt=time_see;//opmode 0일때 cnt초기화 이제 다시 시작하니까 값 입력하기
		TCCR1B = 0x04;//카운터 시작
	}
	else if(opmode == 1) //스탑워치 일시 정지 opmode=0이고 cnt초기화 되니까 cnt 값 저장
	{
		//TCCR1B = (TCCR1B)? 0x00:0x04;//정지는 opmode =0로 이동 나중에 수정하기
		TCCR1B = 0x00;
		opmode=0;
		time = time_see;
	} //타이머 시작 정지
	else if(opmode == 2) time_var++;//시간 설정
	else if(opmode == 3) //타이머 시간 감소시 타이머 켜고 끄기
	{
		TCCR1B = (TCCR1B)? 0x00:0x04;
		
	}
	else if(opmode ==4) opmode=0;//타이머 종료
}
ISR(INT5_vect)// 시간설정 모드 / 이후 다운 
{
	if (opmode == 0)//스톱워치 리셋
	{
		TCCR1B = 0x00;
		cnt=0;
		
		opmode = 0;
		time_see=0;
		time = time_see;
	}
	else if (opmode == 1)//스톱워치 작동시 리셋
	{
		TCCR1B = 0x00;
		cnt=0;
		
		opmode = 0;
		time_see=0;
		time = time_see;
	}
	else if(opmode == 2) time_var--;//시간 설정
	else if(opmode == 3)//타이머 카운트중 리셋
	{
		TCCR1B = 0x00;
		cnt=0;
		
		opmode=0;
		time=0;
		time_see=0;
		
	}
	else if(opmode ==4) opmode=0;
}
ISR(INT6_vect)// 리셋버튼 시간 설정 모드시 칸 이동
{
	if(opmode == 0)//타이머 시간 설정 모드
	{
		opmode = 2;
		select = 3;
		state = 0;
		//time = time_see;
	}
	else if(opmode == 1) //스톱워치중 초기화
	{
		TCCR1B = 0x00;
		cnt=0;
		
		opmode = 0;
		time_see=0;
		time = time_see;
		
	}
	else if(opmode == 2) //타이머 시간 설정 모드
	{
		
		state++;
		
	}
	else if(opmode ==3) //타이머 시간 감소시 타이머 설정 모드로
	{
		TCCR1B = 0x00;
		time = time_see;//실제 남은 시간 저장
		cnt=0;//타이머 카운터 초기화
		
		opmode=2;//타이머 시간설정
		select = 3;//타이머 3(3~0)번째 자리
		state = 0;//맨 처음 입력 단계
		//cnt=0;
		
	}
	else if(opmode ==4) opmode=0;
}