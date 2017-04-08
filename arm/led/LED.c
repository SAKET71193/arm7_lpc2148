/********************************************************/
/* This Program is to demonstrate the LED Functionality */
/*******************************************************
Author 		: saket
Board 		: arm 7
Processor 	: LPC2148

LED Mapping 	: LED0 thru LED7 : P1.24 thru P1.31

Jumper Settings :

********************************************************/

#include<lpc214x.h>

//LED Mapping for the board

#define LED_MASK 0xFF000000
#define LED0  24

void delay(unsigned int time)
{
unsigned int i,j;
	for(i = 0; i < time ;i++ )
	{
		for(j = 0; j < 5000 ; j++);
	}
}

int main(void)
{
	//PINSEL2 &= 0xFFFFFFF3;	// set PORT1 as GPIO
	PINSEL2 = 0;

 	IODIR1 = LED_MASK;			// set the direction of the pins as  output : 1

	while(1)
	{
			IOSET1 = LED_MASK;					// set the port pins to 1
			delay(150);
			IOCLR1 = LED_MASK;					//clear the port pins to 0
			delay(150);
	} 
}
