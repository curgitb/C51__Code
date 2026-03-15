#include <REGX52.H>
#include "Key.h"
#include "Nixie.h"
#include "Timer0.h"

//定义引脚
sbit LED=P2^0;
sbit Motor=P1^0;


unsigned char Count,Compare;
unsigned char KeyNum,Speed;

void main()
{
	Timer0Init();			//定时器0初始化
	while(1)
	{	
		KeyNum=Key();
		if(KeyNum==1)		//按键一进行电机速度切换
		{
			Speed++;
			Speed%=4;
		}
		if(Speed==0) {Compare=0;}		//不同档位对应的比较值
		if(Speed==1) {Compare=50;}
		if(Speed==2) {Compare=75;}
		if(Speed==3) {Compare=100;}
		
		Nixie(1,Speed);		//数码管显示当前电机的档位值
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
		Motor=1;	//电机启动
	}
	else
	{
		Motor=0;	//电机停止
	}	
}