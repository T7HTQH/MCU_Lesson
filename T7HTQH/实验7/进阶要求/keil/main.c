#include <reg51.h>

sbit key=P3^2;

unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
						//定义数码管显示数组
unsigned char rec_con;	//定义接收变量

void Uart_Init()		//串口初始化，晶振频率为11.0592MHZ，波特率为9600
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
	unsigned char con;	//定义计数变量
	Uart_Init();		//串口初始化
	while(1)			//死循环
	{
		if(key==0)		//如果按键按下
		{
			con++;		//将con+1
			if(con==16)
			{
				con=0;
			}
			SBUF=con;	//将con发送给另一个单片机
			while(!TI);	//等待发送完成
			TI=0;		//清除发送完成标志位
			while(!key);//按键松手检测
		}
		if(rec_con<16)	//防止数码管显示数组越界
		{
			P2=seg[rec_con];	//显示接收到的数组
		}
	
	}
	
}

void Uart_out() interrupt 4		//串口中断函数
{
	if(RI)						//检测是否有接收
	{
		rec_con=SBUF;			//将SBUF中的值转移到rec_con
		RI=0;					//清除接收标志位
	}
}

