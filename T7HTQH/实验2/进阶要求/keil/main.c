#include <reg51.h>
#include <math.h>

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
	P3=0xff;
	P2=0x00;
	switch(where)
	{
		case 1:seg1=0;;P2=seg[num];break;
		case 2:seg2=0;P2=seg[num];break;
		case 3:seg3=0;P2=seg[num];break;
		case 4:seg4=0;P2=seg[num];break;
		case 5:seg5=0;P2=seg[num];break;
		case 6:seg6=0;P2=seg[num];break;
	}
	if(point)
	{
		P2=P2|0x80;
	}
}

void seg_showln(float number)
{
	long int what=0;
	char point_where=6;
	if(number<10)
	{
		point_where=1;
	}
	else if(number<100)
	{
		point_where=2;
	}
	else if(number<1000)
	{
		point_where=3;
	}
	else if(number<10000)
	{
		point_where=4;
	}
	else if(number<100000)
	{
		point_where=5;
	}
	what=number*pow(10,point_where);
	switch(point_where)
	{
		case 1:	seg_show(1,what/100000%10,0);
						seg_show(2,what/10000%10,0);
						seg_show(3,what/1000%10,0);
						seg_show(4,what/100%10,0);
						seg_show(5,what/10%10,1);
						seg_show(6,what%10,0);
						break;
		case 2:	seg_show(1,what/100000%10,0);
						seg_show(2,what/10000%10,0);
						seg_show(3,what/1000%10,0);
						seg_show(4,what/100%10,1);
						seg_show(5,what/10%10,0);
						seg_show(6,what%10,0);
						break;
		case 3:	seg_show(1,what/100000%10,0);
						seg_show(2,what/10000%10,0);
						seg_show(3,what/1000%10,1);
						seg_show(4,what/100%10,0);
						seg_show(5,what/10%10,0);
						seg_show(6,what%10,0);
						break;
		case 4:	seg_show(1,what/100000%10,0);
						seg_show(2,what/10000%10,1);
						seg_show(3,what/1000%10,0);
						seg_show(4,what/100%10,0);
						seg_show(5,what/10%10,0);
						seg_show(6,what%10,0);
						break;
		case 5:	seg_show(1,what/100000%10,1);
						seg_show(2,what/10000%10,0);
						seg_show(3,what/1000%10,0);
						seg_show(4,what/100%10,0);
						seg_show(5,what/10%10,0);
						seg_show(6,what%10,0);
						break;
		default:seg_show(1,what/100000%10,0);
						seg_show(2,what/10000%10,0);
						seg_show(3,what/1000%10,0);
						seg_show(4,what/100%10,0);
						seg_show(5,what/10%10,0);
						seg_show(6,what%10,0);
						break;
	}
}

void main()
{
	while(1)
	{
		seg_showln(1234.5);
	}
	
}