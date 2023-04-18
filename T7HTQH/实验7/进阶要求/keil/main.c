#include <reg51.h>

sbit key=P3^2;

unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
						//�����������ʾ����
unsigned char rec_con;	//������ձ���

void Uart_Init()		//���ڳ�ʼ��������Ƶ��Ϊ11.0592MHZ��������Ϊ9600
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xFD;			//���ö�ʱ��ʼֵ
	TH1 = 0xFD;			//���ö�ʱ����ֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
	ES=1;
	EA=1;
}

void main()
{
	unsigned char con;	//�����������
	Uart_Init();		//���ڳ�ʼ��
	while(1)			//��ѭ��
	{
		if(key==0)		//�����������
		{
			con++;		//��con+1
			if(con==16)
			{
				con=0;
			}
			SBUF=con;	//��con���͸���һ����Ƭ��
			while(!TI);	//�ȴ��������
			TI=0;		//���������ɱ�־λ
			while(!key);//�������ּ��
		}
		if(rec_con<16)	//��ֹ�������ʾ����Խ��
		{
			P2=seg[rec_con];	//��ʾ���յ�������
		}
	
	}
	
}

void Uart_out() interrupt 4		//�����жϺ���
{
	if(RI)						//����Ƿ��н���
	{
		rec_con=SBUF;			//��SBUF�е�ֵת�Ƶ�rec_con
		RI=0;					//������ձ�־λ
	}
}

