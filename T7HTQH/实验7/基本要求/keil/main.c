#include <reg52.h>

void UartInit(void)
{
	PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
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
	UartInit();
//	SBUF=0x61;
//	while(!TI);
	while(1)
	{
		
	}
}

void Uart_out() interrupt 4
{
	unsigned int rec;
	if(1)
	{
		
		rec=SBUF;
		RI=0;
		SBUF=rec-32;
		while(!TI);
		TI=0;
	}
}