#include <REGX52.H>

//I2C SCL(Serial Clock) SDA(Serial Data)引脚定义
sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

/**
 * @brief	I2C开始
 * @param 	无
 * @retval 	无
 */
void I2C_Start(void)
{
	I2C_SDA=1;		//先将SDA拉高，再将SCL拉高，在SCL为高电平期间，SDA不能随意变动
	I2C_SCL=1;
	I2C_SDA=0;
	I2C_SCL=0;
}

/**
 * @brief	I2C结束
 * @param 	无
 * @retval 	无
 */
void I2C_Stop(void)
{
	I2C_SCL=0;
	I2C_SDA=0;
	I2C_SCL=1;	
	I2C_SDA=1;
}

/**
 * @brief	I2C发送一个字节
 * @param 	Byte 要发送的这个字节数据
 * @retval 	无
 */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	
	for(i=0;i<8;i++)	//逐次将SDA上的数据发送出去
	{
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		I2C_SCL=0;
	}
	
}

/**
 * @brief	I2C接收一个字节
 * @param 	无
 * @retval 	接收到的字节数据
 */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char Byte=0x00,i;
	
	I2C_SDA=1;		//先将SDA上的数据释放
	for(i=0;i<8;i++)	//逐次将SDA上的数据读取进来
	{
		if(I2C_SDA) {Byte |= (0x80>>i);}
		I2C_SCL=1;
		I2C_SCL=0;
	}
	
	return Byte;
}

/**
 * @brief	I2C发送应答
 * @param 	AckBit I2C发送应答位，0为应答，1为非应答
 * @retval 	无
 */
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA=AckBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/**
 * @brief	I2C接收应答
 * @param 	无
* @retval 	接收到的应答位，0为应答，1为非应答
 */
unsigned char I2C_ReceiveAck(void)
{
	unsigned char AckBit;
	
	I2C_SDA=1;		//先将SDA上的数据释放
	AckBit=I2C_SDA;	
	I2C_SCL=1;	
	I2C_SCL=0;
	
	return AckBit;
}