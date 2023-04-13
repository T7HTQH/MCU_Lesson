#include <reg51.h>

sbit key=P3^2;

unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

unsigned char rec_con;

void Uart_Init()
{
	PCON &= 0x7F;		//波特率不倍速
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
	unsigned char con;
	Uart_Init();
	while(1)
	{
		if(key==0)
		{
			con++;
			if(con==16)
			{
				con=0;
			}
			SBUF=con;
			while(!TI);
			TI=0;
			while(!key);
		}
		if(rec_con<16)
		{
			P2=seg[rec_con];
		}
	
	}
	
}

void Uart_out() interrupt 4
{
	if(RI)
	{
		rec_con=SBUF;
		RI=0;
	}
}

