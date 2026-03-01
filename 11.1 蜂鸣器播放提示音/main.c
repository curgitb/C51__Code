#include <REGX52.H>
#include "Nixie.h"
#include "Key.h"
#include "Buzzer.h"

unsigned char KeyNum;

void main()
{

	Nixie(1,0);		//数码管初始显示为0；
	while(1)
	{
		KeyNum=Key();	//获取按键键码值
		if(KeyNum)
		{
			Nixie(1,KeyNum);	//数码管显示按键键码
			Buzzer_Time(100);	//蜂鸣器持续发声
		}
	}
}