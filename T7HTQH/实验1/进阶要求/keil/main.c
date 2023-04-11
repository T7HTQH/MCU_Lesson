#include <reg51.h>

sbit key3 = P1^4;

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
	unsigned char i;
	if(key3==0)
	{
			while(1)
			{
				for(i=0;i<8;i++)
				{
						P2=0x01<<i;
					delay_ms(1000);
					
				}
				if(key3==1)
				{
					break;
				}
			}	
	}
}


void led_show()
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
			P2=0x80>>i;
		delay_ms(1000);
	}
}

void main()
{
		while(1)
		{
			key_scan();
			led_show();
		}
}