#include "lpc214x.h"
#include "stdio.h"
#include "SPI.h"
#include "card.h"
#include "UART.h"



int main()
{ 
	UartInit(9600);		 							//Initialize UART with 9600 baudrate
	printf("\nHello\n");
	printf("Program for MicroSD card\n\n");  
	delay(5000);
	card_init();									//Initialize SD Card
	delay(5000);  
	card_csd(); 			 						//Display card's capacity
	card_cid();										//Display card info
	delay(5000);  
	card_write(0x1234,0x42);						//Write data 0x42 to sector 0x1234
	delay(5000);
	card_read(0x1234);								//Read data from sector 0x1234
	while(1);							   			//Stop here
	return 0;
}
