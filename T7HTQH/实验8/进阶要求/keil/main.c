#include <reg51.h>

sbit CS=P3^1;        //Ƭѡ�˿�
sbit SCK =P3^0;      //ʱ�Ӷ˿�
sbit DIN=P3^2;       //��������

unsigned int con=0;

void Timer0_Init(void)		//10����@12.000MHz
{
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0xF0;				//���ö�ʱ��ʼֵ
	TH0 = 0xD8;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0=1;					//������ʱ��0�ж�
	EA=1;						//�������ж�
}

void DA_OUTPUT(unsigned int adata)	//DA�������
{
	unsigned char i;		//�����������
	adata<<=6;				//����������6λ
	SCK=0;					//����SCK
	CS=0;					//����CS
	for(i=0;i<12;i++)
	{
		SCK=0;				//����SCK
		adata<<=1;			//��adata����
		DIN=CY;				//�۲�adata���ƺ��Ƿ�����������������1��������0��
		SCK=1;				//����SCK
	}
	CS=1;					//����CS
	SCK=0;					//����SCK
}


void main(void)//0.01s==10ms
{
	Timer0_Init();				//��ʱ����ʼ��
	while(1)							//��ѭ��
	{
		con+=5;						//DA���ÿ�����ӵ�ֵ��ȷ����ֵ��ѹΪ1V
		DA_OUTPUT(con);		//�����ѹ
	}
}

void out() interrupt 1 	//�жϺ���
{
	
		con=0;							//����ѹֵ��0

}

