#include <REGX52.H>
#include "UART.h"

void main()
{
	UART_Init();	//串口初始化
	while(1)
	{	
		
		
	}
}

void UART_Routine() interrupt 4	//串口中断程序
{
	if(RI==1)	//当接收标志位置1时，串口向电脑发送收到的值，并取反LED0;
	{
		P2=~SBUF;	
		UART_SendByte(SBUF);
		RI=0;
	}
}