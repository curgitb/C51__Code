#include <REGX52.H>
#include "Delay.h"

sbit SER=P3^4;	//Serial	定义串行数据口
sbit RCK=P3^5;	//Receive Clock	定义接收时钟口
sbit SCK=P3^6;	//Serial Clock	定义串行数据发送时钟口

/**
 * @brief	点阵屏显示
 * @param 	Location	点阵屏要显示的列（段选）	范围：0~7，0表示第一列，7表示第八列
 * @param 	Data		点阵屏所选列要显示的数据（位选）	
 * @retval 	无
 */
void MatrixLED_Show(unsigned char Location,Data)
{
	unsigned char i=0;
	P0=0xFF;	//清零显示点阵屏
	RCK=0;		//时钟初始化
	SCK=0;	
	for(i=0;i<8;i++)	//（位选）数据串行输入并行输出
	{
		SER=(0x80>>i)&Data;		//通过循环不断选中数据的每一位
		SCK=1;					//上升沿输入74HC595数据
		SCK=0;					//清零串行数据时钟

	}
	RCK=1;						//上升沿并行输出数据
	RCK=0;						//清零接收时钟
	P0=~(0x80>>Location);		//点亮所选择列的LED;
	Delay(1);					//延时1ms， 保证亮度

}
