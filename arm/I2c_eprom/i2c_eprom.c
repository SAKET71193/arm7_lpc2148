#include "LPC214x.h"
#include "UART.h"
#include "stdio.h"

#define EEPROM_Addr 0xA0		  	//device address
#define I2Cwrite	0x00			//LSB bit 0 (write)
#define I2Cread		0x01			//LSB bit 1 (read)

#define I2C_ENABLE 	1 << 6		   //I2C Enable bit
#define I2C_START	1 << 5		   //Start Bit
#define I2C_STOP 	1 << 4		   //Stop Bit
#define I2C_SI		1 << 3		   //I2C interrupt flag
#define I2C_AACK  	1 << 2		   //assert ACK flag

unsigned char write_array[10] = {0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0xC5};
unsigned char read_array[10];


void I2CInit(void)
{
	PINSEL0 &= 0xFFFFFF0F;							//set the pins for i2c functions
	PINSEL0 |= 0x00000050;							//P0.2 -> SCL0		P0.3 -> SDA0
	
	I2C0CONCLR  = I2C_ENABLE | I2C_START | I2C_STOP | I2C_SI | I2C_AACK;	//clear all the bits in CONTROL register
	
	//set I2C clock to work at 100Khz 
	I2C0SCLH = 0x4B ;							//set the high time of i2c clock; (15mhz / 100khz / 2)
	I2C0SCLL = 0x4B ;							//set the low time of i2c clock;
	
	I2C0CONSET = I2C_ENABLE ;					//enable the I2C Interface
}										


void I2CStart(void)								  //Function to initiate a start condition on the I2C bus
{
unsigned int status;	
I2C0CONCLR = (I2C_START | I2C_STOP | I2C_SI | I2C_AACK); 	// clear all the bits in CONCLR register	
I2C0CONSET = (I2C_ENABLE );					 		  		//Enable the I2C interface 
I2C0CONSET = (I2C_START);					  				//set the STA bit 
while(!((status=I2C0CONSET)& I2C_SI));						//wait till interrupt flag becomes set
}


void I2CStop(void)
{
unsigned int status;					 
I2C0CONCLR = I2C_START | I2C_SI | I2C_AACK;				//clear all bits 
I2C0CONSET = I2C_STOP;										//set STOP bit
}


void I2Csend(unsigned char data)
{	   
unsigned int status;
I2C0DAT = data;
I2C0CONCLR = I2C_START | I2C_STOP ;						// clear start bit for next operation 
I2C0CONCLR = I2C_SI;									// clear interrupt flag
while(!((status=I2C0CONSET)& I2C_SI));				   	//wait till interrupt flag becomes set
}

unsigned char I2Cget(void)
{
unsigned char data;
unsigned int status;

I2C0CONCLR = I2C_START | I2C_STOP;		
I2C0CONCLR = I2C_SI;									// clear interrupt flag				
I2C0CONSET = I2C_AACK;								   	// send ack to continue further data transfer
while(!((status=I2C0CONSET)& I2C_SI));					//wait till interrupt flag becomes set
data = I2C0DAT;
return data;
}


int main()
{
unsigned int i;
UartInit(9600);					  //initialize UART with 9600 baudrate
printf("\nI2C EEPROM\n\n");
I2CInit();						  //initialize I2C


 	/* Write Sequence */ 
printf("Writing Data.....\n");
I2CStart();							//Assert START
I2Csend(EEPROM_Addr | I2Cwrite);	 //Device address with LSB bit 0
I2Csend(0x13);		   				//Address higher byte
I2Csend(0x49);						//Address lower byte
for(i=0;i<10;i++)
	I2Csend(write_array[i]); 		//write the array to EEPROM
I2CStop();							//Assert STOP


	/* Read Sequence */
printf("\nReading.....\n\n");
I2CStart();							 //Assert START
I2Csend(EEPROM_Addr | I2Cwrite);	 //Device address with LSB bit 0 (Dummy Write)
I2Csend(0x13);						//Address higher byte
I2Csend(0x49);			 			//Address lower byte
I2CStart();							//Assert Restart
I2Csend(EEPROM_Addr | I2Cread);		//Device address with LSB bit 1
for(i=0;i<10;i++)
	read_array[i] = I2Cget(); 		//Read EEPROM
I2CStop();							//Assert STOP


	/*Display Write and Read Data*/
for(i=0;i<10;i++)
	printf("write_array[%d] = 0x%02X\tread_array[%d] = 0x%02X\n", i, write_array[i], i, read_array[i]);		  //display write and read data


while(1);	 			 //stop here forever
return 0;
}
