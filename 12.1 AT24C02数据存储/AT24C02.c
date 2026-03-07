#include "I2C.h"

/*AT24C02的固定地址为1010，可配置地址本开发板上为000
	所以SLAVE ADDRESS+W为0xA0，SLAVE ADDRESS+R为0xA1
	则定义AT24C02的写入地址为0xA0*/
#define SlaveAddress 0xA0

/**
 * @brief	AT24C02写入一个字节
 * @param 	WordAddress 要写入的字地址
 * @param 	Data 要写入的数据
 * @retval 	无
 */void AT24C02_WriteByte(unsigned char WordAddress,Data)
{
	I2C_Start();
	I2C_SendByte(SlaveAddress);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
}

/**
 * @brief	AT24C02读出一个字节
 * @param 	WordAddress 要读出数据所在的字地址
 * @retval 	读出的数据
 */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	
	I2C_Start();
	I2C_SendByte(SlaveAddress);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(SlaveAddress | 0x01);	
	I2C_ReceiveAck();
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	
	return Data;
}