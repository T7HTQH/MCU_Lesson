#include <reg51.h>

sbit CS=P3^1;        //Ƭѡ�˿�
sbit SCK =P3^0;      //ʱ�Ӷ˿�
sbit DIN=P3^2;       //��������

void DA_OUTPUT(unsigned int adata)
{
	unsigned char i;
	adata<<=6;
	SCK=0;
	CS=0;
	for(i=0;i<12;i++)
	{
		SCK=0;
		adata<<=1;
		DIN=CY;
		SCK=1;
	}
	CS=1;
	SCK=0;
}


void main(void)
{
	unsigned int i;
	while(1)
	{
		for(i=0;i<200;i+=4)
		{
			DA_OUTPUT(i);
		}
	}
}

