#include <REGX52.H>

/**
 * @brief   定时器0初始化，计时周期为1ms
 * @param   无
 * @retval  无
 */
 
void Timer1Init(void)		//1000微秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	EA=1;           //设置总体开中断
	ET0=1;			//设置允许定时器0中断
	PT0=0;			//设置定时器0的中断优先级
}

//void Timer0_Routine() interrupt 1
//{
//	static unsigned int T0Count;
//	
//	TL0 = 0x66;		//设置定时初值
//	TH0 = 0xFC;		//设置定时初值
//	T0Count++;
//	if(T0Count>=1000)
//	{
//	
//		T0Count=0;
//	}
//}