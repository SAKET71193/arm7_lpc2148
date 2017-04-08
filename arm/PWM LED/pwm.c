#include <lpc214x.h>

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<1000;j++);
}

int main()
{
	unsigned int period=1000, i;
	PINSEL1 &= 0xFFFFF3FF;		// Pin 0.21 as PWM5 pin
	PINSEL1 |= 0x00000400;

	PWMPR = 0x00;
	PWMMCR = 0x00000002;

	PWMMR0 = period;
	PWMMR5 = period/2;

	PWMLER = 0x000000021;
	PWMPCR = 0x00002000;
	PWMTCR =  0x00000009;			   	//Enable PWM and TC
	
	while(1)
	{
		for(i=0;i<period;i++)
		{
			PWMMR5 = i;
			PWMLER = 0x000000021;
			delay(10);	
		}
		for(i=period;i>0;i--)
		{
			PWMMR5 = i;
			PWMLER = 0x000000021;
			delay(10);	
		}
	}
}
