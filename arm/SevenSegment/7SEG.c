/*
Pin Configuration
A		- 	P1.16
B		-	P1.17
C		-	P1.18
D		-	P1.19
E		-	P1.20
F		-	P1.21
G		-	P1.22
DOT		-	P1.23
SEG1	-	P0.10
SEG2	-	P0.11
*/
#include"lpc214x.h"

#define SEG_A  1<<16			   // SEGMENT 	A
#define SEG_B  1<<17			   // SEGMENT 	B
#define SEG_C  1<<18			   // SEGMENT 	C
#define SEG_D  1<<19			   // SEGMENT 	D
#define SEG_E  1<<20			   // SEGMENT 	E
#define SEG_F  1<<21			   // SEGMENT 	F
#define SEG_G  1<<22			   // SEGMENT 	G
#define SEG_DP 1<<23			   // SEGMENT 	DECIMAL POINT
#define SEG1   1<<10
#define SEG2   1<<11

#define ONE 	(SEG_B | SEG_C)	   										//DATA FOR SHOWING '1'
#define TWO 	(SEG_A | SEG_B | SEG_D | SEG_E | SEG_G)					//DATA FOR SHOWING '2'
#define THREE 	(SEG_A | SEG_B | SEG_C | SEG_D | SEG_G)					//DATA FOR SHOWING '3'
#define FOUR 	(SEG_B | SEG_C | SEG_F | SEG_G)							//DATA FOR SHOWING '4'
#define FIVE 	(SEG_A | SEG_C | SEG_D | SEG_F | SEG_G)					//DATA FOR SHOWING '5'
#define SIX 	(SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)			//DATA FOR SHOWING '6'
#define SEVEN 	(SEG_A | SEG_B | SEG_C)	   								//DATA FOR SHOWING '7'
#define EIGHT 	(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)	//DATA FOR SHOWING '8'
#define NINE 	(SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G)			//DATA FOR SHOWING '9'
#define ZERO 	(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F)			//DATA FOR SHOWING '0'
#define AA 		(SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G)			//DATA FOR SHOWING 'A'
#define BB 		(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)	//DATA FOR SHOWING 'B'
#define CC 		(SEG_A | SEG_D | SEG_E | SEG_F)							//DATA FOR SHOWING 'C'
#define DD 		(SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F )		//DATA FOR SHOWING 'D'
#define EE 		(SEG_A | SEG_D | SEG_E | SEG_F | SEG_G)			        //DATA FOR SHOWING 'E'
#define FF 		(SEG_A | SEG_E | SEG_F | SEG_G)					        //DATA FOR SHOWING 'F'
#define DP 		(SEG_DP)												//DATA FOR SHOWING '.'
#define SSEG_MASK   	(SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G|SEG_DP)

unsigned int seg_data[]={ZERO , ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN,EIGHT,\
						  NINE, AA, BB, CC, DD, EE, FF, DP };

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
 	int i,j;

	PINSEL0 &= 0xFF0FFFFF;				//P0.10 and P.11 as GPIO
  	PINSEL2 = 0xFFFFFFF3;				//PORT1 as GPIO
	IO0DIR = SEG1 | SEG2;
  	IO1DIR = SSEG_MASK;	// set the direction of the pins
  	IO1SET= SSEG_MASK;	// set the direction of the pins

	while(1)
 	{
		for(i =0 ; i < 99 ; i++ )
		{
			for(j=0; j<30; j++)
			{
				IO0SET = SEG1;
				IO0CLR = SEG2;

				IO1CLR = seg_data[i/10];	// since the 7 seg display is common anode we have to clear the port pins to make SEGMENT
				delay(2);
				IO1SET = seg_data[i/10];

				IO0CLR = SEG1;
				IO0SET = SEG2;

				IO1CLR = seg_data[i%10];	// since the 7 seg display is common anode we have to clear the port pins to make SEGMENT
				delay(2);
				IO1SET = seg_data[i%10];
			}

		}
 	}
}
