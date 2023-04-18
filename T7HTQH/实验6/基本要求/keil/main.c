#include <reg51.h>

sbit LED=P2^0;				//定义LED引脚

unsigned int con;			//定义中间变量

void Timer_init()				//设置定时器0每100us进入一次中断
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x02;			//设置定时器模式
	TL0 = 0x9C;				//设置定时初始值
	TH0 = 0x9C;				//设置定时重载值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0=1;					//打开定时器0中断
	EA=1;					//打开总中断

}

void main()
{
	Timer_init();			//定时器初始化
	while(1)				//死循环
	{

	}
}

void Timer0_out() interrupt 1	//定时器0中断函数
{
	con++;
	if(con==10000)
	{
		con=0;
		LED=!LED;				//计到10000，即1s时翻转LED状态
	}
}
