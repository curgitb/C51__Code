#include <REGX52.H>
#include "LCD1602.h"
#include "MatrixKey.h"


unsigned char KeyNum;
unsigned int Password,Count;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while(1)
	{
		KeyNum=MatrixKey();
		if(KeyNum)  // 如果有按键按下才显示
		{
			if(KeyNum<=10) // 当S1~S10按下时，输入密码，且按下S10时输入数字0
			{
				if(Count<4)  // 控制密码位数为4
				{
					Password*=10;  // 将密码左移1位
					Password+=KeyNum%10;
					Count++;					
				}
				LCD_ShowNum(2,1,Password,4);  // 更新显示			
			}
			if(KeyNum==11)  // 当按下S11时，表示确认
			{
				if(Password==2003)
				{					
					LCD_ShowString(1,14,"OK ");  // 密码正确，显示OK
					Password=0;  // 密码清零
					Count=0;	//  计数清零		
					LCD_ShowNum(2,1,Password,4);  // 清空Password的值并更新显示
				}
				else
				{					
					LCD_ShowString(1,14,"ERR");  // 密码错误，显示ERR
					Password=0;  // 密码清零
					Count=0;	//  计数清零		
					LCD_ShowNum(2,1,Password,4);  // 清空Password的值并更新显示
				}
			}
			if(KeyNum==12) // 当按下S12时，表示取消
			{
				Password=0;  // 密码清零
				Count=0;	//  计数清零		
				LCD_ShowNum(2,1,Password,4);  // 清空Password的值并更新显示
			}
			
		}
			
	}
}
