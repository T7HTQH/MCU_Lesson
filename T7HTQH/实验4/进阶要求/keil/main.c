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
	IT1=0;							//将外部中断1设置为低电平触发
	EX1=1;							//打开外部中断1
	EX0=1;							//打开外部中断0
	PX1=1;							//将外部中断1的优先级设置为高
	EA=1;							//打开总中断
	while(1)						//未触发中断时的显示
	{
		P2=0xff;
	}

}

void out_1() interrupt 0			//外部中断0的中断函数
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

void out_2() interrupt 2			//外部中断1的中断函数
{
	P2=0x55;
	delay_ms(1000);
	delay_ms(1000);
	P2=0xaa;
	delay_ms(1000);
	delay_ms(1000);
	P2=0x55;
	delay_ms(1000);
	delay_ms(1000);
	P2=0xaa;
	delay_ms(1000);
	delay_ms(1000);
}
