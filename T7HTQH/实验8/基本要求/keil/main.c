#include <reg51.h>

sbit CS=P3^1;        //Ƭѡ�˿�
sbit SCK =P3^0;      //ʱ�Ӷ˿�
sbit DIN=P3^2;       //��������

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


void main(void)
{
	unsigned char i;		//�����������
	while(1)				//��ѭ��
	{
		for(i=0;i<100;i++)	//0~100�����Ϊ����������������
		{
			DA_OUTPUT(i);
		}
		for(i=100;i>0;i++)	//100~0�����Ϊ�ݼ������½�����
		{
			DA_OUTPUT(i);
		}
	}
}

