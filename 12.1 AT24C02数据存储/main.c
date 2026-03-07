#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"
#include "Key.h"
#include "AT24C02.h"

unsigned char KeyNum;	//键码值
unsigned int Num;		//要显示的数据

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Hello!");
	LCD_ShowNum(2,1,Num,5);			//初始化LCD显示
	while(1)
	{
		KeyNum=Key();	//获取键码值
		if(KeyNum==1)	//按键1按下，数据+1
		{
			Num++;
			LCD_ShowNum(2,1,Num,5);
		}
		if(KeyNum==2)	//按键2按下，数据-1
		{
			Num--;
			LCD_ShowNum(2,1,Num,5);
		}
		if(KeyNum==3)	//按键3按下，将数据写入AT24C02，E2PROM，掉电不丢失
		{
			AT24C02_WriteByte(0,Num%256);
			Delay(5);
			AT24C02_WriteByte(1,Num/256);
			LCD_ShowString(2,1,"Write OK!");
			Delay(1000);
			LCD_ShowString(2,1,"         ");
		}
		if(KeyNum==4)	//按键4按下，从AT24C02中读出数据，E2PROM，掉电不丢失
		{
			Num=AT24C02_ReadByte(0);
			Num|=AT24C02_ReadByte(1)<<8;
			LCD_ShowNum(2,1,Num,5);			
		}
	}
}