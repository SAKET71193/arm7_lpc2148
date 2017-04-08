 /***************************************************************/
/* This Program is to demonstrate the onchip RTC Functionality */
/****************************************************************
Author 		: saket
Board 		: arm7
Processor 	: LPC2148

*****************************************************************/
#include"lpc214x.h"
#include<stdio.h>

#define RTConPrescaler 1 		// should be 1 if using PCLK for clock source else 0 for external oscillator


extern void UartInit(unsigned int ); 			// function defined in serial.c

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i = 0; i < time ;i++ )
		for(j = 0; j < 5000 ; j++);
}

void RTCInit(void)
{
	CIIR = 0x00;				 // no interrupt to be generated
#ifdef RTConPrescaler
	PREINT = 0x16D;				 // assuming 15 mhz PCLK.
	PREFRAC = 0x1B00;			 // assuming 15 mhz PCLK.
    CCR = 0x02;
#else
	CCR = 0x02;
#endif
}

void SetTime(int hours, int mins, int sec)
{
	SEC  = sec;				// program the secs
	MIN  = mins;			// program the mins
	HOUR = hours;			// program the hours

	CCR =  0x01;			// start the clock
}

int main(void)
{
	UartInit(9600);

	RTCInit();
	SetTime(5,30,01);

	while(1)
	{
		printf("\nThe Time is ");
		printf(":%02d",HOUR);
		printf(":%02d",MIN);
		printf(":%02d",SEC);
		delay(500);
	}
return 0;
}
