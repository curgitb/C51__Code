#include <REGX52.H>
#include "Delay.h"
#include "UART.h"

unsigned char Sec;	//通过串口向电脑发送数据，从零开始，数据每秒递增1

void main()
{
	UART_Init();	//串口初始化
	while(1)
	{	
		UART_SendByte(Sec);		//串口向电脑发送1字节数据
		Sec++;
		Delay(1000);	//延时1s

	}
}

