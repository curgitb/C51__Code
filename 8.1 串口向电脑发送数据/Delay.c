#include <INTRINS.H>

/**
 * @brief  延时函数
 * @param  需要延时的ms数，范围:0~65535
 * @retval  无
 */

void Delay(unsigned int xms)		//@11.0592MHz
{
	unsigned char i, j;

	while(xms--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}
