/*
**	Stepper Motor Interfaced to pins P0.4 to P0.7
*/
#include <lpc214x.h>

#define STP0		1<<4
#define STP1		1<<5
#define STP2		1<<6
#define STP3		1<<7   
#define STP_MASK	STP0 | STP1 | STP2 | STP3

unsigned int full_step[] = {STP0|STP2, STP0|STP3, STP1|STP3, STP1|STP2};

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<5000;j++);
}

int main()
{
	unsigned int i,j;
	PINSEL0 &= ~0x0000FF00;
	IODIR0 |= STP_MASK;
	IOSET0 = STP_MASK;
	while(1)
	{
		for(j=0;j<20;j++)	   			/* Clockwise rotation	*/
		{	
			for(i=0;i<4;i++)
			{
				IOCLR0 = full_step[i];
				delay(10);
				IOSET0 = STP_MASK;
				delay(10);
			}
		}
		delay(1000);

		for(j=0;j<20;j++)				/*	Anticlockwise rotation	*/
		{	
			for(i=0;i<4;i++)
			{
				IOCLR0 = full_step[3-i];
				delay(10);
				IOSET0 = STP_MASK;
				delay(10);
			}
		}
		delay(1000);
	}
}
