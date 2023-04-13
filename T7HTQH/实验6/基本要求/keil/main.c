#include <reg51.h>

sbit LED=P2^0;

unsigned int con;

void Timer_init()
{
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x02;			//���ö�ʱ��ģʽ
	TL0 = 0x9C;				//���ö�ʱ��ʼֵ
	TH0 = 0x9C;				//���ö�ʱ����ֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0=1;
	EA=1;

}

void main()
{
	Timer_init();
	while(1)
	{

	}
}

void Timer0_out() interrupt 1
{
	con++;
	if(con==10000)
	{
		con=0;
		LED=!LED;
	}
}