#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

//蜂鸣器引脚定义
sbit Buzzer=P2^5;

//C调音符对应频率，再转换为定时器的重装载值
unsigned int FreqTable[]={
	63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64524,//低音
	64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030,//中音
	65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283,//高音
};

//小星星
unsigned int code Music[]={
	12,12,19,19,21,21,19,19,17,17,16,16,14,14,12,12,19,19,17,17,16,16,14,14,
	19,19,17,17,16,16,14,14,12,12,19,19,21,21,19,19,17,17,16,16,14,14,12,12,
	
	
	0xFF,
};
unsigned char FreqSelect,MusicSelect;//蜂鸣器发声频率选择位与音乐音高选择位

void main()
{
	Timer0Init();	//定时器初始化
	
	while(1)
	{
		if(Music[MusicSelect]!=0xFF)	//	当选择频率不是终止位时
		{
			FreqSelect=Music[MusicSelect];	
			Delay(500);
			MusicSelect++;	
			
			TR0=0;
			Delay(5);	//音符间短暂停顿
			TR0=1;
		
		}
		else		// 音乐播放完毕后继续播放
		{
			MusicSelect=0;
			FreqSelect=Music[MusicSelect];
			
		}
		
	}
}

void Timer0_Routine() interrupt 1
{
	
	TL0 = FreqTable[FreqSelect]%256;		//设置定时初值
	TH0 = FreqTable[FreqSelect]/256;		//设置定时初值
	Buzzer=!Buzzer;		//蜂鸣器反转发声

	
}