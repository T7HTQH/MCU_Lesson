#include <reg51.h>

unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

unsigned int second=30,min=24,hour=13,con;

void delay_ms(unsigned int t)
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}
}

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
	unsigned char i,watch;
	Timer_init();
	
	while(1)
	{
			for(i=0;i<6;i++)
			{
				P3=~(0x01<<i);
				switch(i)
				{
					case 0:watch=hour/10%10;break;
					case 1:watch=hour%10;break;
					case 2:watch=min/10%10;break;
					case 3:watch=min%10;break;
					case 4:watch=second/10%10;break;
					case 5:watch=second%10;break;
				}
				
				P2=seg[watch];
				delay_ms(1);
				}
		

	}
}

void Timer0_out() interrupt 1
{
	con++;
	if(con==10000)
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
