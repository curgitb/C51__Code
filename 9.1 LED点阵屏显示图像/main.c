#include <REGX52.H>
#include "Delay.h"
#include "MatrixLED.h"


unsigned char MatrixLED[]={0x3C,0x42,0xA9,0x85,0x85,0xA9,0x42,0x3C};//每列所要显示的数据
unsigned char Column;

void main()
{
	while(1)
	{
		for(Column=0;Column<8;Column++)		//循环显示每列数据，点亮LED点阵屏
		{
			MatrixLED_Show(Column,MatrixLED[Column]);

		}
	}
}