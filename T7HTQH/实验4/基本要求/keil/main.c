#include <reg51.h>

void delay_ms(unsigned int t)
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}
}

void main()
{
	IT0=0;
	EX0=1;
	EA=1;
	while(1)
	{
		P2=0xff;
	}

}

void out() interrupt 0
{
	P2=0x00;
	delay_ms(1000);
	delay_ms(1000);
	P2=0xff;
	delay_ms(1000);
	delay_ms(1000);
	P2=0x00;
	delay_ms(1000);
	delay_ms(1000);
	P2=0xff;
	delay_ms(1000);
	delay_ms(1000);
}