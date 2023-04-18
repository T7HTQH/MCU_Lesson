#include <reg52.h>

void UartInit(void)		//波特率初始化 晶振频率为11.0592MHZ，波特率为19200
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFD;			//设置定时初始值
	TH1 = 0xFD;			//设置定时重载值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时

	ES=1;				//开启串口中断
	EA=1;				//开启总中断
}

void main()
{
	UartInit();			//串口初始化
	while(1)
	{
		
	}
}

void Uart_out() interrupt 4		//串口中断函数
{
	unsigned int rec;			//定义接收变量
	if(RI)						//如果有接收
	{
		rec=SBUF;				//将SBUF的值转移进rec
		RI=0;					//清除接收标志位
		SBUF=rec-32;			//将接收到的字母通过ASCII值转化为大写发送
		while(!TI);				//等待发送完成
		TI=0;					//清除发送标志位
	}
}
