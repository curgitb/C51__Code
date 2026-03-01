#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Key.h"
#include "Timer0.h"


unsigned char MODE,KeyNum,TimeSetSelect,TimeSetFlashFlag;

void TimeShow(void)//时间显示功能
{
	DS1302_ReadTime();		//读取芯片时间
	LCD_ShowNum(1,1,DS1302_Time[0],2);	//显示年
	LCD_ShowNum(1,4,DS1302_Time[1],2);	//显示月
	LCD_ShowNum(1,7,DS1302_Time[2],2);	//显示日
	LCD_ShowNum(2,1,DS1302_Time[3],2);	//显示时
	LCD_ShowNum(2,4,DS1302_Time[4],2);	//显示分
	LCD_ShowNum(2,7,DS1302_Time[5],2);	//显示秒
	LCD_ShowNum(1,10,DS1302_Time[6],1);	//显示星期
}

void TimeSet(void)//时间设置功能
{
	if(KeyNum==2)//按键2按下
	{
		TimeSetSelect++;	//时间设置选择位加1
		TimeSetSelect%=7;	//时间设置选择位大于6清零
	}
	if(KeyNum==3)//按键3按下
	{
		DS1302_Time[TimeSetSelect]++;	//所选时间加1
		if(DS1302_Time[0]>99)	{DS1302_Time[0]=00;}	//年溢出判断
		if(DS1302_Time[1]>12)	{DS1302_Time[1]=01;}	//月溢出判断
		if(DS1302_Time[1]==1 || DS1302_Time[1] ==3 || DS1302_Time[1] ==5 || DS1302_Time[1] ==7 ||
			 DS1302_Time[1] ==8 || DS1302_Time[1] ==10 || DS1302_Time[1] ==12)//日溢出判断
		{
			if(DS1302_Time[2]>31)	{DS1302_Time[2]=01;}
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1] ==6 || DS1302_Time[1] ==9 || DS1302_Time[1] ==11)
		{
			if(DS1302_Time[2]>30)	{DS1302_Time[2]=01;}
		}
		else if(DS1302_Time[1]==2)	//2月单独判断，是否闰年
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]>29)	{DS1302_Time[2]=01;}	
			}
			else
			{
				if(DS1302_Time[2]>28)	{DS1302_Time[2]=01;}	
			}
		}
		if(DS1302_Time[3]>23)	{DS1302_Time[3]=00;}	//时溢出判断
		if(DS1302_Time[4]>59)	{DS1302_Time[4]=00;}	//分溢出判断
		if(DS1302_Time[5]>59)	{DS1302_Time[5]=00;}	//秒溢出判断
		if(DS1302_Time[6]>7)	{DS1302_Time[6]=1;}		//星期溢出判断
	}
	if(KeyNum==4)//按键4按下
	{
		DS1302_Time[TimeSetSelect]--;	//所选时间减1
		if(DS1302_Time[0]<0)	{DS1302_Time[0]=99;}	//年溢出判断
		if(DS1302_Time[1]<1)	{DS1302_Time[1]=12;}	//月溢出判断
		if(DS1302_Time[1]==1 || DS1302_Time[1] ==3 || DS1302_Time[1] ==5 || DS1302_Time[1] ==7 ||
			 DS1302_Time[1] ==8 || DS1302_Time[1] ==10 || DS1302_Time[1] ==12)	//日溢出判断
		{
			if(DS1302_Time[2]<1)	{DS1302_Time[2]=31;}
			if(DS1302_Time[2]>31)	{DS1302_Time[2]=01;}
		}
		else if(DS1302_Time[1]==4 || DS1302_Time[1] ==6 || DS1302_Time[1] ==9 || DS1302_Time[1] ==11)
		{
			if(DS1302_Time[2]<1)	{DS1302_Time[2]=30;}
			if(DS1302_Time[2]>30)	{DS1302_Time[2]=01;}
		}
		else if(DS1302_Time[1]==2)	//2月单独判断，是否闰年
		{
			if(DS1302_Time[0]%4==0)
			{
				if(DS1302_Time[2]<1)	{DS1302_Time[2]=29;}	
				if(DS1302_Time[2]>29)	{DS1302_Time[2]=01;}	
			}
			else
			{
				if(DS1302_Time[2]<1)	{DS1302_Time[2]=28;}	
				if(DS1302_Time[2]>28)	{DS1302_Time[2]=01;}	
			}
		}
		if(DS1302_Time[3]<0)	{DS1302_Time[3]=23;}	//时溢出判断
		if(DS1302_Time[4]<0)	{DS1302_Time[4]=59;}	//分溢出判断
		if(DS1302_Time[5]<0)	{DS1302_Time[5]=59;}	//秒溢出判断
		if(DS1302_Time[6]<1)	{DS1302_Time[6]=7;}		//星期溢出判断
	}
	//更新显示与闪烁
	if(TimeSetSelect==0 && TimeSetFlashFlag==1)	{LCD_ShowString(1,1,"  ");}
	else {	LCD_ShowNum(1,1,DS1302_Time[0],2);}	//显示年
	if(TimeSetSelect==1 && TimeSetFlashFlag==1)	{LCD_ShowString(1,4,"  ");}
	else {	LCD_ShowNum(1,4,DS1302_Time[1],2);}	//显示月
	if(TimeSetSelect==2 && TimeSetFlashFlag==1)	{LCD_ShowString(1,7,"  ");}
	else {	LCD_ShowNum(1,7,DS1302_Time[2],2);}	//显示日
	if(TimeSetSelect==3 && TimeSetFlashFlag==1)	{LCD_ShowString(2,1,"  ");}
	else {	LCD_ShowNum(2,1,DS1302_Time[3],2);}	//显示时
	if(TimeSetSelect==4 && TimeSetFlashFlag==1)	{LCD_ShowString(2,4,"  ");}
	else {	LCD_ShowNum(2,4,DS1302_Time[4],2);}	//显示分
	if(TimeSetSelect==5 && TimeSetFlashFlag==1)	{LCD_ShowString(2,7,"  ");}
	else {	LCD_ShowNum(2,7,DS1302_Time[5],2);}	//显示秒
	if(TimeSetSelect==6 && TimeSetFlashFlag==1)	{LCD_ShowString(1,10,"  ");}
	else {	LCD_ShowNum(1,10,DS1302_Time[6],1);}//显示星期
}


void main()
{
	LCD_Init();			//LCD液晶显示屏初始化
	DS1302_Init();		//DS1302时钟芯片初始化
	Timer0Init();		//定时器0初始化
	LCD_ShowString(1,1,"  -  -  ");		//显示静态字符
	LCD_ShowString(2,1,"  :  :  ");
	
	DS1302_SetTime();		//设置芯片时间
	while(1)
	{
		KeyNum=Key();	//按键检测	
		if(KeyNum==1)	//按键1按下时，切换时间显示与时间设置模式
		{
			if(MODE==0)	{MODE=1;TimeSetSelect=0;}	//切换到时间设置模式，并将时间设置选择位清零
			else if(MODE==1)	{MODE=0;DS1302_SetTime();}	//切换到时间显示模式，并把设置的时间写入芯片
		}
		switch(MODE)		//判断时间模式，执行相应的程序
		{
			case 0:	TimeShow();break;
			case 1:	TimeSet();break;
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
		TimeSetFlashFlag=!TimeSetFlashFlag;		//时间设置闪烁标志位取反
		T0Count=0;
	}
}