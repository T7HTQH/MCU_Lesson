#include <reg51.h>

sbit seg1=P3^0;
sbit seg2=P3^1;

unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
									//定义数码管显示数组

int con=0;							//定义定时器计数变量

void delay_ms(unsigned char t)		//定义毫秒延时函数
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}
}

void timer_init()
{
	TMOD=0x05;						//将定时器0设置为计数器模式
	TL0=0;							//设置定时器初值
	TH0=0;
	TR0=1;							//开启定时器0
}

void seg_show(unsigned char n)		//数码管显示函数
{
	P2=0;
	seg1=0;seg2=1;
	P2=seg[n/10%10];				//显示十位上的数字
	delay_ms(30);
	P2=0;
	seg1=1;seg2=0;
	P2=seg[n%10];					//显示个位上的数字
	delay_ms(30);
}

void main()
{
	timer_init();					//定时器0初始化
	while(1)						//死循环
	{
		con=TL0+(TH0>>8);			//将定时器的计数值赋给con
		seg_show(con);				//显示con
	}
}
