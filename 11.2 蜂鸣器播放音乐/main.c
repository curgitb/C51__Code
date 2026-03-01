#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

//蜂鸣器引脚定义

sbit Buzzer=P2^5;

//
#define P	0 		
#define L1	1		
#define L1_	2			
#define L2	3		
#define L2_	4		
#define L3	5		
#define L4	6		
#define L4_	7		
#define L5	8		
#define L5_	9		
#define L6	10		
#define L6_	11		
#define L7	12		

#define M1	13		
#define M1_	14			
#define M2	15		
#define M2_	16		
#define M3	17		
#define M4	18		
#define M4_	19		
#define M5	20		
#define M5_	21		
#define M6	22		
#define M6_	23		
#define M7	24		

#define H1	25		
#define H1_	26			
#define H2	27		
#define H2_	28		
#define H3	29		
#define H4	30		
#define H4_	31		
#define H5	32		
#define H5_	33		
#define H6	34		
#define H6_	35		
#define H7	36		


//C调音符对应频率，再转换为定时器的重装载值
unsigned int FreqTable[]={
	0,
	63628,63731,63835,63928,64021,64103,64185,64260,64331,64400,64463,64524,//低音
	64580,64633,64684,64732,64777,64820,64860,64898,64934,64968,65000,65030,//中音
	65058,65085,65110,65134,65157,65178,65198,65217,65235,65252,65268,65283,//高音
};

//天空之城	音高+时长
unsigned int code Music[]={
	//1
	M1,4,
	M1,4,
	M5,4,
	M5,4,
	
	M6,4,
	M6,4,
	M5,4+4,
	
	M4,4,
	M4,4,
	M3,4,
	M3,4,
	
	M2,4,
	M2,4,
	M1,4+4,
	
	M5,4,
	M5,4,
	M4,4,
	M4,4,
	
	M3,4,
	M3,4,
	M2,4+4,
	
	//2
	M5,4,
	M5,4,
	M4,4,
	M4,4,
	
	M3,4,
	M3,4,
	M2,4+4,
	
	M1,4,
	M1,4,
	M5,4,
	M5,4,
	
	M6,4,
	M6,4,
	M5,4+4,
	
	M4,4,
	M4,4,
	M3,4,
	M3,4,
	
	M2,4,
	M2,4,
	M1,4+4,
	
	
	
	
	
	
	0xFF,
};
unsigned char FreqSelect,MusicSelect;//蜂鸣器发声频率选择位与音乐音高选择位

void main()
{
	Timer0Init();	//定时器初始化
	
	while(1)
	{
		if(FreqSelect!=0xFF)	//	当选择频率不是终止位时
		{
			FreqSelect=Music[MusicSelect];
			MusicSelect++;			
			Delay(MusicSelect*125);			
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