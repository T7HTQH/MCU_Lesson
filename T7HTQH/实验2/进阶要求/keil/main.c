#include <reg51.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

sbit seg1=P3^0;
sbit seg2=P3^1;
sbit seg3=P3^2;
sbit seg4=P3^3;
sbit seg5=P3^4;
sbit seg6=P3^5;

void delay_ms(unsigned char t)
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}
}

void seg_show(unsigned char where,unsigned int num,unsigned char point)
{
	switch(where)
	{
		case 1:P3=0xff&(~(0x01));P2=seg[num];break;
		case 2:P3=0xff&(~(0x01<<1));P2=seg[num];break;
		case 3:P3=0xff&(~(0x01<<2));P2=seg[num];break;
		case 4:P3=0xff&(~(0x01<<3));P2=seg[num];break;
		case 5:P3=0xff&(~(0x01<<4));P2=seg[num];break;
		case 6:P3=0xff&(~(0x01<<5));P2=seg[num];break;
	}
	if(point==1)
	{
		P2=P2|0x80;
	}
	if(where<6)
	{
		delay_ms(8);
	}
	
}

void seg_showln(float number)
{
	unsigned char change[7];
	unsigned char con=0,i=0,point_flag=0;
	sprintf(change,"%f",number);
	point_flag=0;
	for(i=0;i<8;)
	{
		
		if(change[i]=='.')
		{
			point_flag=1;
			con=i;
			seg_show(i,change[i-1]-48,point_flag);
		}
		else if(!(point_flag==1&&change[i]=='0'))
		{
			seg_show(i+1-point_flag,change[i]-48,0);
		}
		i++;
		
	}
}

void main()
{
	while(1)
	{
		seg_showln(1.56);
	}
	
}