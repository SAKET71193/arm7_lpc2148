/***************************************************************/
/* This Program is to demonstrate the On Chip DAC Functionality */
/****************************************************************
Author 		: saket
Board 		: SBC_ARM7
Processor 	: LPC2148

DAC  Mapping :  DAC Output (AOUT)-> P0.25


Jumper Settings :  No jumper selection

*****************************************************************/

#include"LPC214x.h"

#define DAC_DataMask 0x0000FFC0
#define DataShift 6

void DACInit(void)
{
	PINSEL1 &= 0xFFF3FFFF;	   	//Set P0.25 as AOUT Pin for analog output
	PINSEL1 |= 0x00080000;
	
	DACR = 1 << 16 ; 			//set the settling time to 2.5us and max current to 300uA
}

void delay(unsigned int time)
{
	unsigned int i,j;
	
	for(i = 0; i < time; i++ )
		for(j = 0; j < 10000 ; j++);
}

int main(void)
{
	int i;

  	DACInit();						// initialsie the DAC interface

 	while(1)
 	{
	 	for(i = 0 ; i < 1024 ;i++ )		// send data to DAC
	  	{
	  		DACR = ( DAC_DataMask &	(i << DataShift));
	  		delay(2);
	  	}
	  	for(i = 1023 ; i > 0 ;i-- )		// send data to DAC
	  	{
	  		DACR = ( DAC_DataMask &	(i << DataShift));
	  		delay(2);
	  	}
	}
}
