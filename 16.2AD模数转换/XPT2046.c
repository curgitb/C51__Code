#include <REGX52.H>

//XPT2046引脚定义
sbit XPT2046_DIN=P3^4;
sbit XPT2046_CS=P3^5;
sbit XPT2046_DCLK=P3^6;
sbit XPT2046_DOUT=P3^7;

/**
 * @brief	XPT2046读取AD值
 * @param 	Command 命令字，范围：头文件内定义的宏，结尾的数字表示转换的位数
 * @retval 	AD转换后的数字量，范围：8位：0~255，12位：0~4095
 */
unsigned int  XPT2046_ReadAD(unsigned char Command)
{
	unsigned int Data=0;	
	unsigned char i;
	XPT2046_DCLK=0;
	XPT2046_CS=0;	
	for(i=0;i<8;i++)		//发送命令字
	{
		XPT2046_DIN=Command & (0x80>>i);
		XPT2046_DCLK=1;
		XPT2046_DCLK=0;
	}
	for(i=0;i<16;i++)		//接收16位数据
	{
		XPT2046_DCLK=1;
		XPT2046_DCLK=0;		
		if(XPT2046_DOUT)
		{
			Data|= (0x8000>>i);
		}		
	}
	XPT2046_CS=1;		
	return Data>>8;
}


