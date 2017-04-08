#include "adc.h"
#include "LCD.h"
#include <stdio.h>

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<5000;j++);
}

int main()
{
	unsigned int temp;
	char buf[16];

	LCD_init();
	ADCInit();
	while(1)
	{
		temp = ADC_Read(2)/2;								//read AN0.2
		sprintf(buf,"Temp: %2d'C",(temp*330)/1024);		//convert to string and store in a buffer
		LCD_display(1,1,buf);					   		//display buffer
		delay(20);
	}
}
