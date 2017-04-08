 /***************************************************************/
/* This Program is to demonstrate the Serial Port Functionality */
/****************************************************************
Author 		: SAKET
Board 		: ARM7
Processor 	: LPC2148

UART 0 Mapping : TxD0 -> P0.0
				 RxD0 -> P0.1

Jumper Settings :	None

*****************************************************************/

#include "lpc214x.h"
#include <stdio.h>

extern void UartInit(unsigned int );	  //setting the baud rate for 9600 baud
extern unsigned char UART_GetChar(void);
extern int UART_PutChar(unsigned char);

/*===================================================================================*/
int main(void)
{
   	UartInit(9600);			// initialise the UART0
   	printf("\r\nThis is a Demonstration for \r\nUART peripheral for LPC2148\r\nDone on SBC_ARM7 Board \r\n");
   	printf("\r\nHit any Key on your PC Keyboard to see result\r\n");

	while(1)
	{
		UART_PutChar(UART_GetChar()); 		//Echo
	}
}
