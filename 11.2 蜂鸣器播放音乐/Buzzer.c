#include <REGX52.H>
#include "INTRINS.h"

//蜂鸣器引脚定义
sbit Buzzer=P2^5;

/**
 * @brief	蜂鸣器私有延时函数，延时500us
 * @param 	无
 * @retval 	无
 */
void Buzzer_Delay500us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 227;
	while (--i);
}

/**
 * @brief	蜂鸣器发声
 * @param 	xms	蜂鸣器发声时长
 * @retval 	无
 */
void Buzzer_Time(unsigned int xms)
{
	unsigned int i;	
	for(i=0;i<xms*2;i++)		//循环加倍，等于发声时长
	{
		Buzzer=!Buzzer;			//引脚反转，蜂鸣器发声
		Buzzer_Delay500us();	//蜂鸣器发声频率为1000HZ
	}

}