#include <reg51.h>

sbit seg1=P3^0;
sbit seg2=P3^1;

unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

int con=0;

void delay_ms(unsigned char t)
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}
}

void timer_init()
{
	TMOD=0x06;
	TL0=236;
	TH0=236;
	TR0=1;
	ET0=1;
	EA=1;
}

void seg_show(unsigned char n)
{
	P2=0;
	seg1=0;seg2=1;
	P2=seg[n/10%10];
	delay_ms(30);
	P2=0;
	seg1=1;seg2=0;
	P2=seg[n%10];
	delay_ms(30);
}

void main()
{
	timer_init();
	while(1)
	{
		con=TL0+(TH0>>8)-236;
		seg_show(con);
	}
}

void out() interrupt 1
{
	con=0;
}