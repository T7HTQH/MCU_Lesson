#include <reg51.h>

//��BUG��Ҳ������ˣ����Ͽ��� 4.18

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
	unsigned int i;			//�����������
	while(1)
	{
		for(i=0;i<200;i+=4)		//ֻ���������ֵ�DA���������ͻ����Ϊ��ݲ�
		{						//i�����ֵΪ200��iÿ�μ�4����һ�����������50��
			DA_OUTPUT(i);		//
		}
	}
}

