#include <reg51.h>

sbit key1 = P1^0;
sbit key2 = P1^2;

unsigned char key_number; 

void delay_ms(unsigned char t)
{
	unsigned char i;
	while(t--)
	{
		for(i=0;i<110;i++);
	}

}

void key_scan()
{
		if(key1==0||key2==0)
		{
			delay_ms(10);
			if(key1==0)
			{
				key_number=1;
			}
			else if(key2==0)
			{
				key_number=2;
			}
		}
}

void main()
{
		while(1)
		{
			key_scan();
			switch(key_number)
			{
				case 1:P2=0xf0;break;
				case 2:P2=0x55;break;
				default:P2=0x00;break;
			}
		}
}