#include <reg51.h>

sbit key3 = P1^4; 						//定于P1^4为按键引脚

unsigned char key_number; 				//定义键值变量

void delay_ms(unsigned char t)			//定义毫秒延时函数
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}

}

void key_scan()							//定义按键扫描函数
{
	unsigned char i;
	if(key3==0)							//按键按下的情况
	{
			while(1)					//松手检测，如果按键弹起则跳出while循环
			{
				for(i=0;i<8;i++)
				{
						P2=0x01<<i;		//利用二进制移位实现流水灯
					delay_ms(1000);
					
				}
				if(key3==1)
				{
					break;
				}
			}	
	}
}


void led_show()							//按键未按下时的流水灯函数
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
			P2=0x80>>i;					//利用二进制移位实现流水灯
		delay_ms(1000);
	}
}

void main()
{
		while(1)						//死循环
		{
			key_scan();					//按键扫描函数
			led_show();					//按键未按下时的流水灯显示
		}
}
