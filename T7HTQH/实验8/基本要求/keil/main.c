#include <reg51.h>

sbit CS=P3^1;        //片选端口
sbit SCK =P3^0;      //时钟端口
sbit DIN=P3^2;       //数据输入

void DA_OUTPUT(unsigned int adata)	//DA输出函数
{
	unsigned char i;		//定义计数变量
	adata<<=6;				//将数据左移6位
	SCK=0;					//拉低SCK
	CS=0;					//拉低CS
	for(i=0;i<12;i++)
	{
		SCK=0;				//拉低SCK
		adata<<=1;			//将adata左移
		DIN=CY;				//观察adata左移后是否有溢出，若溢出则发送1，否则发送0；
		SCK=1;				//拉高SCK
	}
	CS=1;					//拉高CS
	SCK=0;					//拉低SCK
}


void main(void)
{
	unsigned char i;		//定义计数变量
	while(1)				//死循环
	{
		for(i=0;i<100;i++)	//0~100次输出为递增，即上升部分
		{
			DA_OUTPUT(i);
		}
		for(i=100;i>0;i++)	//100~0次输出为递减，即下降部分
		{
			DA_OUTPUT(i);
		}
	}
}

