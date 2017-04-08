#include "lpc214x.h"
#include "stdio.h"
#include "UART.h"
#define ADC0 1 << 24
#define ADC1 1 << 26

void ADCinit()
{
	PINSEL1 &= 0xF0FFFFFF;			//Configure pins P0.28 and P0.29 as ADC pins
	PINSEL1 |= 0x05000000;

	AD0CR = 0x00210302;				//Set Burst mode, CLK_DIV, Channels, 10bit ADC/11 cycles, select AD0.1
	AD0CR |= 1<<24;				   	//Start ADC
}

void timerisr(void) __irq				//Interrupt Service Routine for TIMER
{	 
	unsigned int ad1_data;
	T0IR = 0xFF;				 		//Clear Interrupt Sources
	if(AD0GDR & 0x80000000)		   		//Check DONE bit
		{
			ad1_data = (AD0GDR & 0x0000FFC0)>>6;			//Assign ADC result to ad1_data n display in mV
			printf("\nADC Voltage (mV) = %4d",(ad1_data*3300)/1024);
		}
	VICVectAddr = 0;		   		//Acknowledge Interrupt
}

void timer_init(void)
{
	T0MR0 = 2000000; 					//Set Match value
	T0MCR = 0x03;	 					//Generate Interrupt and reset TC upon match
	T0PR = 16;					   		//Set prescale
	T0TCR = 1;				  			//Enable counter
	VICVectCntl1 = 0x20 | 4;			//Assign Timer0 interrupt to slot 1
	VICVectAddr1 = (unsigned)timerisr;		//Assign timerisr() interrupt routine to slot 1
	VICIntEnable |= 1<<4;			 	//Enable Timer0 interrupt
}



int main()
{
	UartInit(9600);						 	//Initialize UART
	ADCinit();					   		 	//Initialize ADC
	printf("ADC using TIMER interrupt:\n");
	timer_init();							//Initialize TIMER
	while(1);								//Do Nothing
}
