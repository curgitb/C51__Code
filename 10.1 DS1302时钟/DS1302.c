#include <REGX52.H>

//引脚定义
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;
sbit DS1302_SCLK=P3^6;

//寄存器写入地址/指令定义
#define DS1302_Second 	0x80
#define DS1302_Minute 	0x82
#define DS1302_Hour 	0x84
#define DS1302_Date 	0x86
#define DS1302_Month	0x88
#define DS1302_Day 		0x8A
#define DS1302_Year 	0x8C
#define DS1302_WP 		0x8E

//时间数组，索引0~6分别为年、月、日、时、分、秒、星期
unsigned char DS1302_Time[]={26,02,21,14,28,03,06};

/**
 * @brief		DS1302时钟芯片初始化
 * @param 		无
 * @retval 		无
 */
void DS1302_Init(void)
{
	DS1302_CE=0;
	DS1302_SCLK=0;
}

/**
 * @brief	向DS1302时钟芯片写入单个字节数据，在哪里/写入/什么
 * @param 	Command	指令/地址，指明向哪里写入
 * @param 	Data	数据， 指明写入的数据
 * @retval 	无
 */
void DS1302_WriteByte(unsigned char Command,Data)
{
	
	unsigned char i=0;
	DS1302_CE=1;		//给CE使能，才能完成写入操作
	
	for(i=0;i<8;i++)	//8个上升沿，完成指令的传输
	{

		DS1302_IO=Command & (0x01<<i);
		DS1302_SCLK=1;		
		DS1302_SCLK=0;
		
	}
	for(i=0;i<8;i++)	//8个上升沿，完成数据的写入
	{
		DS1302_IO=Data & (0x01<<i);
		DS1302_SCLK=1;			
		DS1302_SCLK=0;
	}
	
	DS1302_CE=0;
}

/**
 * @brief	从DS1302时钟芯片读取单个字节数据，从哪里/读出/什么
 * @param 	Command	指令/地址，指明从哪里读出
 * @retval 	Data	数据，返回读出的数据
 */
unsigned char DS1302_ReadByte(unsigned char Command)
{
	unsigned char i=0;
	unsigned char Data=0;
	Command|=0x01;		//切换到读的指令/地址
	DS1302_CE=1;		//给CE使能，才能完成读出操作
	
	for(i=0;i<8;i++)	//8个上升沿，完成指令的传输
	{
	
		DS1302_IO=Command & (0x01<<i);
		DS1302_SCLK=0;		
		DS1302_SCLK=1;
		
	}
	for(i=0;i<8;i++)	//8个下降沿，完成数据的读取
	{
		DS1302_SCLK=1;		
		DS1302_SCLK=0;		
		if(DS1302_IO){Data|=(0x01<<i);}

	}
	DS1302_CE=0;	//清零使能位
	DS1302_IO=0;	//读取后将IO设置为0，否则读出的数据会出错
	
	return Data;
}

/**
 * @brief	DS1302设置时间，调用之后，DS1302_Time[]数组中的数据会被送入DS1302中
 * @param 	无
 * @retval 	无
 */
void DS1302_SetTime(void)
{
	DS1302_WriteByte(DS1302_WP,0x00);	//解除写保护
	DS1302_WriteByte(DS1302_Year,DS1302_Time[0]/10*16+DS1302_Time[0]%10);	//将十进制年月日时分秒星期转化为BCD码形式写入DS1302
	DS1302_WriteByte(DS1302_Month,DS1302_Time[1]/10*16+DS1302_Time[1]%10);	
	DS1302_WriteByte(DS1302_Date,DS1302_Time[2]/10*16+DS1302_Time[2]%10);	
	DS1302_WriteByte(DS1302_Hour,DS1302_Time[3]/10*16+DS1302_Time[3]%10);	
	DS1302_WriteByte(DS1302_Minute,DS1302_Time[4]/10*16+DS1302_Time[4]%10);	
	DS1302_WriteByte(DS1302_Second,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_Day,DS1302_Time[6]/10*16+DS1302_Time[6]%10);	
	DS1302_WriteByte(DS1302_WP,0x80);	//打开写保护
}

/**
 * @brief	DS1302读取时间，调用之后，DS1302中的数据会被送入DS1302_Time[]数组中
 * @param 	无
 * @retval 	无
 */
void DS1302_ReadTime(void)
{
	unsigned char Temp=0;
	
	Temp=DS1302_ReadByte(DS1302_Year);	////将DS1302中存储的BCD码时间转化为十进制时间读出
	DS1302_Time[0]=Temp/16*10+Temp%16;				
	Temp=DS1302_ReadByte(DS1302_Month);
	DS1302_Time[1]=Temp/16*10+Temp%16;				
	Temp=DS1302_ReadByte(DS1302_Date);
	DS1302_Time[2]=Temp/16*10+Temp%16;			
	Temp=DS1302_ReadByte(DS1302_Hour);
	DS1302_Time[3]=Temp/16*10+Temp%16;			
	Temp=DS1302_ReadByte(DS1302_Minute);
	DS1302_Time[4]=Temp/16*10+Temp%16;			
	Temp=DS1302_ReadByte(DS1302_Second);
	DS1302_Time[5]=Temp/16*10+Temp%16;				
	Temp=DS1302_ReadByte(DS1302_Day);		
	DS1302_Time[6]=Temp/16*10+Temp%16;			
}