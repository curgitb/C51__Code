#include <REGX52.H>
#include "Delay.h"

unsigned char KeyNumber=0;

unsigned char MatrixKey()
{
	
	
		/*P1=0xFF;  按列扫描
		P1_3=0;
		if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=1;}
		if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=5;}
		if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=9;}
		if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=13;}

		P1=0xFF;
		P1_2=0;
		if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=2;}
		if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=6;}
		if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=10;}
		if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=14;}

		P1=0xFF;
		P1_1=0;
		if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=3;}
		if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=7;}
		if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=11;}
		if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=15;}

		P1=0xFF;
		P1_0=0;
		if(P1_7==0){Delay(20);while(P1_7==0);Delay(20);KeyNumber=4;}
		if(P1_6==0){Delay(20);while(P1_6==0);Delay(20);KeyNumber=8;}
		if(P1_5==0){Delay(20);while(P1_5==0);Delay(20);KeyNumber=12;}
		if(P1_4==0){Delay(20);while(P1_4==0);Delay(20);KeyNumber=16;}
		*/ 
		
		P1=0xFF;  //按行扫描
		P1_7=0;
		if(P1_3==0){Delay(20);while(P1_3==0);Delay(20);KeyNumber=1;}
		if(P1_2==0){Delay(20);while(P1_2==0);Delay(20);KeyNumber=2;}
		if(P1_1==0){Delay(20);while(P1_1==0);Delay(20);KeyNumber=3;}
		if(P1_0==0){Delay(20);while(P1_0==0);Delay(20);KeyNumber=4;}

		P1=0xFF;
		P1_6=0;
		if(P1_3==0){Delay(20);while(P1_3==0);Delay(20);KeyNumber=5;}
		if(P1_2==0){Delay(20);while(P1_2==0);Delay(20);KeyNumber=6;}
		if(P1_1==0){Delay(20);while(P1_1==0);Delay(20);KeyNumber=7;}
		if(P1_0==0){Delay(20);while(P1_0==0);Delay(20);KeyNumber=8;}

		P1=0xFF;
		P1_5=0;
		if(P1_3==0){Delay(20);while(P1_3==0);Delay(20);KeyNumber=9;}
		if(P1_2==0){Delay(20);while(P1_2==0);Delay(20);KeyNumber=10;}
		if(P1_1==0){Delay(20);while(P1_1==0);Delay(20);KeyNumber=11;}
		if(P1_0==0){Delay(20);while(P1_0==0);Delay(20);KeyNumber=12;}

		P1=0xFF;
		P1_4=0;
		if(P1_3==0){Delay(20);while(P1_3==0);Delay(20);KeyNumber=13;}
		if(P1_2==0){Delay(20);while(P1_2==0);Delay(20);KeyNumber=14;}
		if(P1_1==0){Delay(20);while(P1_1==0);Delay(20);KeyNumber=15;}
		if(P1_0==0){Delay(20);while(P1_0==0);Delay(20);KeyNumber=16;}
		return KeyNumber;
}

