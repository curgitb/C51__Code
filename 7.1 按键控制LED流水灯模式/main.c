#include <REGX52.H>
#include "Timer0.h"
#include "Key.h"
#include "INTRINS.h"

unsigned char KeyNum,LEDMode;

void main()
{
	Timer0Init();	//定时器初始化
	P2=0xFE;		//流水灯初始值
	while(1)
	{
		KeyNum=Key();	//按键检测
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				LEDMode++;	//LED模式切换
				
				if(LEDMode>=2)
				{
					LEDMode=0;
				}
			}
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;	
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;		
		if(LEDMode==0)	//当LEDMode等于0时，P2值循环右移，反映在本板上流水灯向左移动
		{
			P2=_cror_(P2,1);
		}
		if(LEDMode==1)	//当LEDMode等于1时，P2值循环左移，反映在本板上流水灯向右移动
		{
			P2=_crol_(P2,1);
		}
		
	}
}
