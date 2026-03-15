#include <REGX52.H>

//引脚定义
sbit LED=P2^0;

//延时函数
void Delay(unsigned char xus)		//@11.0592MHz  100us
{
	while(xus--);
}

void main()
{
	unsigned char Time,Count;		//控制延时时间，来改变LED亮的时间达到呼吸灯的效果
	while(1)
	{
		for(Time=0;Time<100;Time++)			//改变LED亮的时间，来改变LED显示的亮度
		{
			for(Count=0;Count<=20;Count++)		//增加显示时间
			{
				LED=0;	
				Delay(Time);	
				LED=1;	
				Delay(100-Time);			
			}
		}
		for(Time=100;Time>0;Time--)
		{
			for(Count=0;Count<=20;Count++)
			{
				LED=0;	
				Delay(Time);	
				LED=1;	
				Delay(100-Time);				
			}
		
		}		
	}
}