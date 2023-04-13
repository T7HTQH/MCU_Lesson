#include <reg51.h>

sbit LED=P2^0;

unsigned int con;

void Timer_init()
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x02;			//设置定时器模式
	TL0 = 0x9C;				//设置定时初始值
	TH0 = 0x9C;				//设置定时重载值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0=1;
	EA=1;

}

void main()
{
	Timer_init();
	while(1)
	{

	}
}

void Timer0_out() interrupt 1
{
	con++;
	if(con==10000)
	{
		con=0;
		LED=!LED;
	}
}