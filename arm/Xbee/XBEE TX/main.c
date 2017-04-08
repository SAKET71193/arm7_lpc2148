#include <lpc214x.h>
#include <stdio.h>
#include "UART.h"

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<10000;j++);
}

void xbeeString(unsigned char *ch)		   	//function to send a command to zigbee
{
	printf("\r\ncommand: %s",ch);
	printf("response:");
	UART1_PutS(ch);
}

int main()
{	unsigned char temp[20],flag=0,i,*PTR;
	Uart0Init(9600);
	Uart1Init(9600);
	xbeeString("+++");						//enter command mode
	delay(1000);
	xbeeString("AT\r\n");				   	//check if all ok
	delay(1000);
	xbeeString("+++");					 	//enter command mode
	delay(1000);
	xbeeString("ATID 15\r\n");				//change network id to 15
	delay(1000);
	xbeeString("ATCN\r\n");					//exit command mode
	delay(1000);
	xbeeString("HELLO.... This is PAN ID 15\r\n");	  	//send a string on network id 15
	delay(1000);
  while(1);
}
