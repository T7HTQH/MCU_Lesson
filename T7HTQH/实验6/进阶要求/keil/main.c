#include <reg51.h>

unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
											//定义数码管显示数组

unsigned int second=30,min=24,hour=13,con;	//定义显示变量

void delay_ms(unsigned int t)				//定义毫秒延时
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}
}

void Timer_init()			//设置定时器0每100us进入一次中断
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
	unsigned char i,watch;	//定义中间变量
	Timer_init();			//定时器初始化
	
	while(1)				//死循环
	{
			for(i=0;i<6;i++)	//数码管位选
			{
				P3=~(0x01<<i);
				switch(i)
				{
					case 0:watch=hour/10%10;break;	//显示小时的十位数
					case 1:watch=hour%10;break;		//显示小时的个位数
					case 2:watch=min/10%10;break;	//显示分钟的十位数
					case 3:watch=min%10;break;		//显示分钟的个位数
					case 4:watch=second/10%10;break;//显示秒钟的十位数
					case 5:watch=second%10;break;	//显示秒钟的个位数
				}
				
				P2=seg[watch];
				delay_ms(1);	//防止proteus抽风，，，，
				}
		

	}
}

void Timer0_out() interrupt 1	//定时器0中断
{
	con++;
	if(con==10000)				//con计够10000次，即1s后，开始给秒钟++，同时检测是否需要进位
	{
		con=0;
		second++;
		if(second==60)
		{
			second=0;
			min++;
			if(min==60)
			{
				min=0;
				hour++;
				if(hour==24)
				{
					hour=0;
				}
			}
		}
	}
}
