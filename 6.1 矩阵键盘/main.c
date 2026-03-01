#include <REGX52.H>
#include "LCD1602.h"
#include "MatrixKey.h"

void main()
{
	unsigned char KeyNum=0;
	LCD_Init();
	LCD_ShowString(1,1,"MatrixKey:");
	while(1)
	{
		KeyNum=MatrixKey();
		if(KeyNum)
		{
			LCD_ShowNum(2,1,KeyNum,2);
		}
	}
	
}