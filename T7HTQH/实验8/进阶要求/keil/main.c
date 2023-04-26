#include <reg51.h>

sbit CS=P3^1;        //片选端口
sbit SCK =P3^0;      //时钟端口
sbit DIN=P3^2;       //数据输入

unsigned int con=0;

void Timer0_Init(void)		//10毫秒@12.000MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xF0;				//设置定时初始值
	TH0 = 0xD8;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	ET0=1;					//开启定时器0中断
	EA=1;						//开启总中断
}

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


void main(void)//0.01s==10ms
{
	Timer0_Init();				//定时器初始化
	while(1)							//死循环
	{
		con+=5;						//DA输出每次增加的值，确保峰值电压为1V
		DA_OUTPUT(con);		//输出电压
	}
}

void out() interrupt 1 	//中断函数
{
	
		con=0;							//将电压值清0

}

