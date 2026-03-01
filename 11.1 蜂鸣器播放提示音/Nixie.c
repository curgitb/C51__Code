#include <REGX52.H>

//数码管显示数字数组，分别为0~9的显示数据
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

/**
 * @brief	数码管显示
 * @param 	Location 选中要显示的数码管，范围：1~8
 * @param 	Number 要显示的数据，范围：0~9
 * @retval 	无
 */
void Nixie(unsigned char Location,Number)
{
	switch(Location)
	{
		case 1:P2_4=1,P2_3=1,P2_2=1;break;
		case 2:P2_4=1,P2_3=1,P2_2=0;break;
		case 3:P2_4=1,P2_3=0,P2_2=1;break;
		case 4:P2_4=1,P2_3=0,P2_2=0;break;
		case 5:P2_4=0,P2_3=1,P2_2=1;break;
		case 6:P2_4=0,P2_3=1,P2_2=0;break;
		case 7:P2_4=0,P2_3=0,P2_2=1;break;
		case 8:P2_4=0,P2_3=0,P2_2=0;break;
	}

	P0=NixieTable[Number];
}
