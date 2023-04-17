#include <reg51.h>

unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
														//定义共阴极数码管显示数组


sbit seg1=P3^0;											//定义P3^0,P3^1,P3^2,P3^4,P3^5
sbit seg2=P3^1;											//为数码管阴极引脚
sbit seg3=P3^2;
sbit seg4=P3^3;
sbit seg5=P3^4;
sbit seg6=P3^5;

void delay_ms(unsigned char t)							//定义毫秒延时函数
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}
}

void seg_show(unsigned char where,unsigned int num)		//定义单个数码管显示函数
{
	P3=0xff;											//这两句是为了消除共阴极数码管在proteus仿真中出现的
	P2=0x00;											//刷新率过快数据乱码问题

	switch(where)										//对数码管进行位选，并将num显示在数码管上
	{
		case 1:seg1=0;;P2=seg[num];break;
		case 2:seg2=0;P2=seg[num];break;
		case 3:seg3=0;P2=seg[num];break;
		case 4:seg4=0;P2=seg[num];break;
		case 5:seg5=0;P2=seg[num];break;
		case 6:seg6=0;P2=seg[num];break;
	}
}

void seg_showln(long int number)						//定义数码管整体显示函数
{
	long int what=0;									//定义中间变量what，防止long int型数据在传输中出错
	what=number/100000%10;								//将number中的每一位剥离显示
	seg_show(1,what);
	what=number/10000%10;
	seg_show(2,what);
	what=number/1000%10;
	seg_show(3,what);
	what=number/100%10;
	seg_show(4,what);
	what=number/10%10;
	seg_show(5,what);
	what=number%10;
	seg_show(6,what);
	
}

void main()
{
	while(1)
	{
		seg_showln(123456);								//显示123456
	}
	
}
