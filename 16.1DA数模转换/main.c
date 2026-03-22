#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

//引脚定义				数模转换，通过输出PWM波来实现数字信号到模拟信号的转变
sbit DA=P2^1;

unsigned char Count,Compare;
unsigned char KeyNum,Speed;

void main()
{
	Timer0Init();			//定时器0初始化
	while(1)
	{	
		for(Compare=0;Compare<100;Compare++)		//调整比较值来改变PWM占空比
		{
			Delay(10);
		}
		for(Compare=100;Compare>0;Compare--)		//调整比较值来改变PWM占空比
		{
			Delay(10);
		}		
	}
}

void Timer0_Routine() interrupt 1
{
	TL0 = 0xA4;		//设置定时初值    设置计数时间为100us
	TH0 = 0xFF;		//设置定时初值
	Count++;
	Count%=100;		//计数从0-100循环
	if(Count<Compare)	//判断计数值和比较值，以此来进行PWM调波进而控制电机转速
	{
		DA=0;	//LED点亮
	}
	else
	{
		DA=1;	//LED熄灭
	}	
}