#include <reg51.h>

sbit key1 = P1^0;							//定义P1^0,P1^2为按键引脚
sbit key2 = P1^2;

unsigned char key_number; 					//定义变量key_number为1键值

void delay_ms(unsigned char t) 				//定义毫秒延时函数
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}

}

void key_scan() 							//定义按键扫描函数
{
		if(key1==0||key2==0)				//检测两按键引脚状态
		{
			delay_ms(10);
			if(key1==0)						//按键1按下
			{
				key_number=1;
			}
			else if(key2==0)
			{
				key_number=2;				//按键2按下
			}
		}
}

void main()
{
		while(1)							//死循环
		{
			key_scan();						//按键扫描
			switch(key_number)				//检测键值
			{
				case 1:P2=0xf0;break;		//按键1按下的情况
				case 2:P2=0x55;break;		//按键2按下的情况
				default:P2=0x00;break;		//没有按键按下的情况
			}
		}
}
