/******************************************************************************/
/* This Program is to demonstrate the onchip External interrupt Functionality */
/******************************************************************************
Author 		: saket
Board 		: arm7
Processor 	: LPC2148

External Interrupt Pin : P0.30 (EINT3)
*******************************************************************************/
#include "lpc214x.h"
#include "stdio.h"

extern void UartInit(unsigned int);

#define IntPin (1 < 30)
#define ExtInt3 (1 << 17)

unsigned int count=0, set =0;

void delay(unsigned int time)
{
unsigned int i,j;
	for(i = 0; i < time ;i++ )
	{
		for(j = 0; j < 4000 ; j++);
	}
}


void ExtInterruptHandler(void)	__irq
{
	EXTINT = 1 << 3;		/* clear interrupt */
	count++;
	set = 1;						
	VICVectAddr = 0;		/* Acknowledge Interrupt */
}

void InitInterrupt(void)
{
unsigned int pinstatus;

	pinstatus = PINSEL1;								// read the value of pinsel 0 register
	pinstatus &= 0xCFFFFFFF ;
	pinstatus |= 0x20000000 ;				// set the pins as EINT3
	PINSEL1   =  pinstatus;

	VICIntEnClr = ExtInt3;

	EXTMODE = 1 << 3;									// INT3 edge trigger
	EXTPOLAR = 0;										// INT3 is falling edge by default

	VICIntSelect = 0x00;								// select the source of the interrupt

	VICVectAddr0 =(unsigned long) ExtInterruptHandler;	// set the interrupt handler address in the address register
	VICVectCntl0 = 0x20 | 17;					// set the control register so that a unique address is generated when interrupt occurs

	VICIntEnable = ExtInt3;								//
}


int main(void)
{
	UartInit(9600);
	InitInterrupt();
	printf("Welcome to Micro-A7xx\nPress the INT Switch\n");
	while(1)
	{
		if(set)
		{
			printf("\r\nInterrupt Count = %d",count);
			set =0;
		}
	}
return 0;
}
