#ifndef __LCD1602_H__
#define	__LCD1602_H__

void LCD_Init(void);
void LCD_ShowChar(unsigned char Line, unsigned char Column, unsigned char Char);
void LCD_ShowString(unsigned char Line,Column,unsigned char *string);
void LCD_ShowNum(unsigned char Line,Column,int Num,char length);
void LCD_ShowSignedNum(unsigned char Line,Column,int Num,unsigned char length);
void LCD_ShowHexNum(unsigned char Line,Column,unsigned int Num,unsigned char length);
void LCD_ShowBinNum(unsigned char Line,Column,unsigned int Num,unsigned char length);

#endif