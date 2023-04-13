#include <reg52.h>

void UartInit(void)
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;			//设置定时初始值
	TH1 = 0xFD;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时

	ES=1;
	EA=1;
}

void main()
{
	UartInit();
//	SBUF=0x61;
//	while(!TI);
	while(1)
	{
		
	}
}

void Uart_out() interrupt 4
{
	unsigned int rec;
	if(1)
	{
		
		rec=SBUF;
		RI=0;
		SBUF=rec-32;
		while(!TI);
		TI=0;
	}
}