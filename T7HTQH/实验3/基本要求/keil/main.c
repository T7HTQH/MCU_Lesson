#include <reg51.h>

unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
											//定义数码管显示数组


unsigned char key_number;					//定义键值变量

void delay_ms(unsigned int t)				//定义延时函数
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}
}

void key_scan()								//定义按键扫描函数
{
	unsigned char hang,line;				//定义行列变量
	unsigned char where;					//定义中间变量
	P1=0x0f;								//行扫描
	if(P1!=0x0f)
	{
		delay_ms(10);
		where=P1&0x0f;
		switch(where)
		{
			case 0x0e:hang=0;break;
			case 0x0d:hang=1;break;
			case 0x0b:hang=2;break;
			case 0x07:hang=3;break;
		}
		P1=0xf0;							//列扫描
		where=P1&0xf0;
		switch(where)
		{
			case 0xe0:line=0;break;
			case 0xd0:line=1;break;
			case 0xb0:line=2;break;
			case 0x70:line=3;break;
		}
		key_number=hang*4+line;				//将扫描到的行列值转化为键值
	}
	
}

void main()
{
	P3=0；
	while(1)
	{
		key_scan();							//按键扫描
		P2=seg[key_number];					//将键值输出到数码管上
	}
}
