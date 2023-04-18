#include <reg51.h>

void delay_ms(unsigned int t)		//定义毫秒延时函数
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}
}

void main()
{
	IT0=0;							//将外部中断0设置为低电平触发
	EX0=1;							//打开外部中断0
	EA=1;							//打开总中断
	while(1)						//外部中断未触发时的情况
	{
		P2=0xff;
	}

}

void out() interrupt 0				//外部中断0的中断函数
{
	P2=0x00;
	delay_ms(1000);
	delay_ms(1000);
	P2=0xff;
	delay_ms(1000);
	delay_ms(1000);
	P2=0x00;
	delay_ms(1000);
	delay_ms(1000);
	P2=0xff;
	delay_ms(1000);
	delay_ms(1000);
}
