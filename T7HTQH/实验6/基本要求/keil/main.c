#include <reg51.h>

sbit LED=P2^0;				//����LED����

unsigned int con;			//�����м����

void Timer_init()				//���ö�ʱ��0ÿ100us����һ���ж�
{
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x02;			//���ö�ʱ��ģʽ
	TL0 = 0x9C;				//���ö�ʱ��ʼֵ
	TH0 = 0x9C;				//���ö�ʱ����ֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0=1;					//�򿪶�ʱ��0�ж�
	EA=1;					//�����ж�

}

void main()
{
	Timer_init();			//��ʱ����ʼ��
	while(1)				//��ѭ��
	{

	}
}

void Timer0_out() interrupt 1	//��ʱ��0�жϺ���
{
	con++;
	if(con==10000)
	{
		con=0;
		LED=!LED;				//�Ƶ�10000����1sʱ��תLED״̬
	}
}
