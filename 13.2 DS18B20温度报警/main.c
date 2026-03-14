#include <REGX52.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "Key.h"
#include "Delay.h"
#include "Timer0.h"
#include "AT24C02.h"


float T,Temp;
char THigh,TLow;
unsigned char KeyNum;

void main()
{
	DS18B20_ConvertT();			//上电先转换一次温度，防止第一次读数据错误
	Delay(500);					//等待转换完成
	LCD_Init();					//LCD1602初始化
	Timer0_Init();				//定时器0初始化
	THigh=AT24C02_ReadByte(0x00);		//读取AT24C02中存放的温度阈值
	TLow=AT24C02_ReadByte(0x01);
//	if(THigh>125 || TLow<-55 || THigh<=TLow)
//	{
//		THigh=20;			//如果阈值非法，则设为默认值
//		TLow=15;
//	}
	while(1)
	{
		DS18B20_ConvertT();		//温度转换
		T=DS18B20_ReadT();		//温度读取
		LCD_ShowString(1,1,"T:");
		if(T<0)					//显示实时温度
		{
			Temp=-T;
			LCD_ShowChar(1,3,'-');
		}
		else
		{
				Temp=T;
			LCD_ShowChar(1,3,'+');
		}
		LCD_ShowNum(1,4,Temp,3);
		LCD_ShowChar(1,7,'.');
		LCD_ShowNum(1,8,(unsigned long) (Temp*100)%100,2);

		LCD_ShowString(2,1,"TH:");		//显示温度阈值
		LCD_ShowSignedNum(2,4,THigh,3);
		LCD_ShowString(2,9,"TL:");		
		LCD_ShowSignedNum(2,12,TLow,3);
		
		KeyNum=Key();					//按键功能制定
		if(KeyNum)
		{
			if(KeyNum==1)				//增加温度上限阈值
			{
				THigh++;
				if(THigh>=125)
				{
					THigh=125;
				}
			}
			if(KeyNum==2)				//降低温度上限阈值
			{
				THigh--;
				if(THigh<=TLow)
				{
					THigh++;
				}

			}
			if(KeyNum==3)				//增加温度下限阈值
			{
				TLow++;
				if(THigh<=TLow)
				{
					TLow--;
				}
			}
			if(KeyNum==4)				//降低温度下限阈值
			{
				TLow--;
				if(TLow<=-55)
				{
					TLow=-55;
				}
			}
			AT24C02_WriteByte(0x00,THigh);		//将温度阈值写入AT24C02中存储，掉电不丢失，E2PROM
			Delay(5);
			AT24C02_WriteByte(0x01,TLow);
			Delay(5);		
		}
		
		if(T>THigh)						//温度报警显示
		{
			LCD_ShowString(1,13,"OVH");
		}
		else if(T<TLow)
		{
			LCD_ShowString(1,13,"UNL");
		}
		else
		{
			LCD_ShowString(1,13,"   ");		
		}
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=20)
	{
		Key_Loop();			//按键驱动函数，每20ms调用一次
		T0Count=0;
	}
}