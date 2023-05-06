#include <reg51.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


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

void seg_show(unsigned char where,unsigned int num,unsigned char point)//定义单个数码管显示函数，point为小数标志位
{
	switch(where)										//数码管位选
	{
		case 1:P3=0xff&(~(0x01));P2=seg[num];break;
		case 2:P3=0xff&(~(0x01<<1));P2=seg[num];break;
		case 3:P3=0xff&(~(0x01<<2));P2=seg[num];break;
		case 4:P3=0xff&(~(0x01<<3));P2=seg[num];break;
		case 5:P3=0xff&(~(0x01<<4));P2=seg[num];break;
		case 6:P3=0xff&(~(0x01<<5));P2=seg[num];break;
	}
	if(point==1)										//如果point为1，则将数据与0x80相与
	{
		P2=P2|0x80;
	}
	if(where<6)
	{
		delay_ms(8);									//消抖，不知道为什么仿真也会出现数码管抖动
	}
	
}

void seg_showln(float number)							//定义数码管整体显示函数
{
	long int what=0;									//定义中间变量what，防止long int型数据在传输中出错

	unsigned char change[7]="";							//定义中间字符串
	unsigned char con=0,i=0,point_flag=0;				//定义变量以及标记
	
		sprintf(change,"%f",number);					//利用sprintf将小数转化为字符串
		point_flag=0;									//重置小数点标志位
		for(i=0;i<8;)									//没有遇到小数点前正常显示
		{
			
			if(change[i]=='.')							//遇到小数点后将小数点标志位置1
			{
				point_flag=1;
				con=i;
				seg_show(i,change[i-1]-48,point_flag);	//给小数点所在数字显示添加小数点
			}
			else if(point_flag)	//防止小数位后不去除多余的0
			{
				seg_show(i+1-point_flag,change[i]-48,0);
			}
			else
			{
				seg_show(i,change[i-1]-48,0);
			}
			i++;

		}

}

void main()
{
	while(1)											//死循环
	{
		seg_showln(2023.05);								//显示小数
	}
	
}
