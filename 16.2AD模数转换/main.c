#include <REGX52.H>
#include "LCD1602.h"
#include "XPT2046.h"
#include "Delay.h"

unsigned int ADValue;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"ADJ");		//可变电阻器值
	LCD_ShowString(1,5,"NTC");		//热敏电阻器值
	LCD_ShowString(1,9,"GR");		//光敏电阻器值
	while(1)
	{
		ADValue=XPT2046_ReadAD(XPT2046_XP);
		LCD_ShowNum(2,1,ADValue,3);		
		ADValue=XPT2046_ReadAD(XPT2046_YP);
		LCD_ShowNum(2,5,ADValue,3);		
		ADValue=XPT2046_ReadAD(XPT2046_VBAT);
		LCD_ShowNum(2,9,ADValue,3);		

	}
}