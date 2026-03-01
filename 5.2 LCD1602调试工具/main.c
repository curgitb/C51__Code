#include <REGX52.H>
#include "LCD1602.h"
#include "Delay.h"

void main()
{
	unsigned int Result=0;
	LCD_Init();
	LCD_ShowChar(1,1,'A');
	LCD_ShowString(1,3,"Hello");
	LCD_ShowNum(1,9,200,3);
	LCD_ShowSignedNum(1,13,-99,2);
	LCD_ShowHexNum(2,1,0xFF,2);
	LCD_ShowBinNum(2,4,0xAA,8);
	while(1)
	{
		Result++;
		Delay(1000);
		LCD_ShowNum(2,13,Result,3);
	}
}