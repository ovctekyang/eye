#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define KEYP P1  // 指定按键所使用的端口
// LED数码管显示数字0-F的段码数组
uchar LED[17] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,
0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0xf6 };
uchar K;	// 全局变量按键号
void delay(int ms);  // 声明延时函数
/*********按键扫描函数 ***************
*函数功能：检测KEYP.0-KEYP.3上的四个按键
*函数返回值：返回所按下的键号，长按则键号+4，若返回0表示无键按下
************************************ */
uchar keyscan()
{
	uchar K = 0;	// 键号(局部变量K)
	uint i = 0;
	uchar KPS; 					// 按键端口状态 
	KPS = KEYP & 0x0f; // 读取KEYP口低4位到KPS
	if (KPS != 0x0f) // 如不等于0x0f，表示有键按下
	{
		delay(20);	// 延时20ms以消除键抖动干扰
		if ((KEYP & 0x0f) == KPS)  // 再次读取KEYP 口低4位，若仍为KPS，表示该键确按下
		{
			for (i = 0; (KEYP & 0x0f) == KPS; i++)
				// 等待按键释放（释放后不再等于KPS）
			{
				switch (KPS)	 //转换为键号
				{
				case 0x0e:K = 1; break;
				case 0x0d:K = 2; break;
				case 0x0b:K = 3; break;
				case 0x07:K = 4; break;
				}
			}
			if (i > 10000)K += 4;    // 若长按，键值+4, 	}
		}
		return(K);	// 返回键号，0表示无键按下
	}
}

/* 主函数 */
void main()
{
	while (1)   		// 循环
	{
		K = keyscan();   	// 读取键值到K（全局变量）
		if (K != 0)	P2 = LED[K];		// 通过P2口的LED显示返回的键号
	}
}
/* 延时函数 */
void delay(int ms)
{
	unsigned int i = ms * 91;
	for (; i > 0; i--) { ; }
}