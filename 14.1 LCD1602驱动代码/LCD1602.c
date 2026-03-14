#include <REGX52.H>

//LCD1602引脚定义
sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;
#define LCD_D P0

/**
 * @brief	LCD1602内部延时函数，延时1ms
 * @param 	无
 * @retval 	无
 */
void LCD_Delay()		//@11.0592MHz  延时1ms
{
	unsigned char i, j;
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);	
	}
}

/**
 * @brief	LCD1602写入指令
 * @param 	Command 要写入的指令
 * @retval 	无
 */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_D=Command;
	LCD_E=1;
	LCD_Delay();
	LCD_E=0;
	LCD_Delay();
}

/**
 * @brief	LCD1602写入数据
 * @param 	Data 要写入的数据
 * @retval 	无
 */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_D=Data;
	LCD_E=1;
	LCD_Delay();
	LCD_E=0;
	LCD_Delay();
}

/**
 * @brief	LCD1602初始化
 * @param 	无
 * @retval 	无
 */
void LCD_Init(void)
{
	LCD_WriteCommand(0x38);		//八位数据接口，两行显示，5*7点阵
	LCD_WriteCommand(0x0C);		//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);		//数据读写操作后，光标自动加一，画面不动
	LCD_WriteCommand(0x01);		//清屏
}

/**
 * @brief	LCD1602光标设置
 * @param 	Line 要显示的行
 * @param 	Column 要显示的列
 * @retval 	无
 */
void LCD_SetCursor(unsigned char Line,Column)
{
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else
	{
		LCD_WriteCommand((0x80|(Column-1))+0x40);		
	}
}

/**
 * @brief	LCD1602显示字符
 * @param 	Line 要显示的行
 * @param 	Column 要显示的列
 * @param 	Char 要显示的字符
 * @retval 	无
 */
void LCD_ShowChar(unsigned char Line,Column, unsigned char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}

/**
 * @brief	LCD1602显示字符
 * @param 	Line 要显示的行
 * @param 	Column 要显示的列
 * @param 	*string 要显示的字符串指针
 * @retval 	无
 */
void LCD_ShowString(unsigned char Line,Column,unsigned char *string)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;string[i]!='\0';i++)
	{
		LCD_WriteData(string[i]);
	}
}

/**
 * @brief	LCD1602指数计数
 * @param 	x 底数
 * @param 	y 指数
 * @retval 	指数计算的结果
 */
unsigned int LCD_Power(unsigned char x,y)
{
	unsigned int z=1;
	unsigned char i;
	for(i=y;i>0;i--)
	{
		z*=x;
	}
	return z;
}

/**
 * @brief	LCD1602显示数字
 * @param 	Line 要显示的行
 * @param 	Column 要显示的列
 * @param 	Num 要显示的数字
 * @param 	Length 要显示的长度
 * @retval 	无
 */
void LCD_ShowNum(unsigned char Line,Column,unsigned int Num,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);	
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Num/LCD_Power(10,i-1)%10);
	}
}

/**
 * @brief	LCD1602显示有符号数字
 * @param 	Line 要显示的行
 * @param 	Column 要显示的列
 * @param 	Num 要显示的数字
 * @param 	Length 要显示的长度
 * @retval 	无
 */
void LCD_ShowSignedNum(unsigned char Line,Column,int Num,unsigned char Length)
{
	unsigned char i;
	unsigned int Num1;
	LCD_SetCursor(Line,Column);	
	if(Num<0)
	{
		Num1=-Num;
		LCD_ShowChar(Line,Column,'-');
	}
	else
	{
		Num1=Num;
		LCD_ShowChar(Line,Column,'+');	
	}
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Num1/LCD_Power(10,i-1)%10);
	}
}

/**
 * @brief	LCD1602显示十六进制数字
 * @param 	Line 要显示的行
 * @param 	Column 要显示的列
 * @param 	Num 要显示的数字
 * @param 	Length 要显示的长度
 * @retval 	无
 */
void LCD_ShowHexNum(unsigned char Line,Column,unsigned int Num,unsigned char Length)
{
	unsigned char i;
	unsigned int SingleNum;
	LCD_SetCursor(Line,Column);	
	for(i=Length;i>0;i--)
	{
		SingleNum=Num/LCD_Power(16,i-1)%16;
		if(SingleNum>=10)
		{
			LCD_WriteData('A'+SingleNum-10);		
		}
		else
		{
			LCD_WriteData('0'+SingleNum);
		}
	}
}

/**
 * @brief	LCD1602显示二进制数字
 * @param 	Line 要显示的行
 * @param 	Column 要显示的列
 * @param 	Num 要显示的数字
 * @param 	Length 要显示的长度
 * @retval 	无
 */
void LCD_ShowBinNum(unsigned char Line,Column,unsigned int Num,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);	
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Num/LCD_Power(2,i-1)%2);
	}
}