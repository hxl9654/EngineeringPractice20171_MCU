#include<stc15.h>
#include<stdio.h>
#include<string.h>
#include<UART.h>
#include<DHT11.h>
#include<ADC.h>

void Timer0_Init(void)		
{
	AUXR |= 0x80;		
	TMOD &= 0xF0;		
	TL0 = 0xCD;		
	TH0 = 0xD4;		
	TF0 = 0;		
	TR0 = 1;		
	ET0 = 1;
}

void main()
{	
	UART_Conf();
	Timer0_Init();
	EA = 1;
	while(1)
	{
		
		UART_Driver();
	}
}
void UART_Action(unsigned char *dat, unsigned char len)
{
	UART_SendString(dat, len);
}
void Interrupt_Timer0() interrupt 1
{
	static unsigned int t = 0;
	char tempc[50] = {0};
	unsigned int light = 0;
	unsigned char wet, temp;
	t++;
	if(t > 1000)
	{
		t -= 1000;
		light = ADC_Get(0);
		light = (light > 500)?0:(500 - light) / 5;
		temp = DHT11_Read(&wet);
		//sprintf(tempc, "l %u %d %d\n", light, (int)temp, (int)wet);
		sprintf(tempc, "x %u %d %d\n", light, (int)temp, (int)wet);
		//sprintf(tempc, "z %u %d %d\n", light, (int)temp, (int)wet);
		UART_SendString(tempc, strlen(tempc));
	}
	UART_RxMonitor(1);
}