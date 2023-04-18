#include <reg51.h>

unsigned char seg[]={0x3F, 0x06, 0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
											//�����������ʾ����

unsigned int second=30,min=24,hour=13,con;	//������ʾ����

void delay_ms(unsigned int t)				//���������ʱ
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}
}

void Timer_init()			//���ö�ʱ��0ÿ100us����һ���ж�
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
	unsigned char i,watch;	//�����м����
	Timer_init();			//��ʱ����ʼ��
	
	while(1)				//��ѭ��
	{
			for(i=0;i<6;i++)	//�����λѡ
			{
				P3=~(0x01<<i);
				switch(i)
				{
					case 0:watch=hour/10%10;break;	//��ʾСʱ��ʮλ��
					case 1:watch=hour%10;break;		//��ʾСʱ�ĸ�λ��
					case 2:watch=min/10%10;break;	//��ʾ���ӵ�ʮλ��
					case 3:watch=min%10;break;		//��ʾ���ӵĸ�λ��
					case 4:watch=second/10%10;break;//��ʾ���ӵ�ʮλ��
					case 5:watch=second%10;break;	//��ʾ���ӵĸ�λ��
				}
				
				P2=seg[watch];
				delay_ms(1);	//��ֹproteus��磬������
				}
		

	}
}

void Timer0_out() interrupt 1	//��ʱ��0�ж�
{
	con++;
	if(con==10000)				//con�ƹ�10000�Σ���1s�󣬿�ʼ������++��ͬʱ����Ƿ���Ҫ��λ
	{
		con=0;
		second++;
		if(second==60)
		{
			second=0;
			min++;
			if(min==60)
			{
				min=0;
				hour++;
				if(hour==24)
				{
					hour=0;
				}
			}
		}
	}
}
