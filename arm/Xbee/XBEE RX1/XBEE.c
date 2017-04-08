#include <lpc214x.h>
#include <stdio.h>
#include "UART.h"

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<10000;j++);
}

void xbeeString(unsigned char *ch)		  // fuction to send a string to Zigbee
{
	printf("\r\ncommand: %s",ch);
	printf("response:");
	UART1_PutS(ch);
}

int main()
{
	Uart0Init(9600);
	Uart1Init(9600);
	xbeeString("+++");					//enter command mode
	delay(1000);
	xbeeString("AT\r\n");				//check if all ok
	delay(1000);
	xbeeString("ATID 10\r\n");			//change network id to 10	(or 15)
	delay(1000);
	xbeeString("ATCN\r\n");				//exit command mode
	delay(1000);

	while(1);
}
