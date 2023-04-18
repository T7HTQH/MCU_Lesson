#include <reg52.h>

void UartInit(void)		//�����ʳ�ʼ�� ����Ƶ��Ϊ11.0592MHZ��������Ϊ19200
{
	PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
	SCON = 0x50;		//8λ����,�ɱ䲨����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xFD;			//���ö�ʱ��ʼֵ
	TH1 = 0xFD;			//���ö�ʱ����ֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ

	ES=1;				//���������ж�
	EA=1;				//�������ж�
}

void main()
{
	UartInit();			//���ڳ�ʼ��
	while(1)
	{
		
	}
}

void Uart_out() interrupt 4		//�����жϺ���
{
	unsigned int rec;			//������ձ���
	if(RI)						//����н���
	{
		rec=SBUF;				//��SBUF��ֵת�ƽ�rec
		RI=0;					//������ձ�־λ
		SBUF=rec-32;			//�����յ�����ĸͨ��ASCIIֵת��Ϊ��д����
		while(!TI);				//�ȴ��������
		TI=0;					//������ͱ�־λ
	}
}
