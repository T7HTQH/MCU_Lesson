#include <reg51.h>

sbit CS=P3^1;        //片选端口
sbit SCK =P3^0;      //时钟端口
sbit DIN=P3^2;       //数据输入

void DA_OUTPUT(unsigned int adata)
{
	unsigned char i;
	adata<<=6;
	SCK=0;
	CS=0;
	for(i=0;i<12;i++)
	{
		SCK=0;
		adata<<=1;
		DIN=CY;
		SCK=1;
	}
	CS=1;
	SCK=0;
}


void main(void)
{
	unsigned char i;
	while(1)
	{
		for(i=0;i<100;i++)
		{
			DA_OUTPUT(i);
		}
		for(i=100;i>0;i++)
		{
			DA_OUTPUT(i);
		}
	}
}

