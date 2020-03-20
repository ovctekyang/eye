#include <reg51.h>
#define uchar unsigned char
#define KEYP P1  // 指定按键所使用的端口
uchar LED[17] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0xf6 };
// LED数码管显示数字0-F的段码
uchar K;	// 全局变量
void delay(int ms); // 声明延时函数
/*************** 行列矩阵按键扫描函数 *********************
*函数功能：检测识别连接到KEYP口上的16个按键，P.7-P.4 为列， P.0-P.3为行
*函数返回值：返回所按下的键号1-9，A-H，若返回0表示无键按下
********************************************************** */
uchar keyRC(void)
{
	uchar R;			//行值
	uchar C;			//列值
	KEYP = 0x0f;     //4根列线输出0000,行线输出 1111
	R = KEYP & 0x0f;   //读入行线值
	if (R != 0x0f)    	//若行线值不为1111，即检测到有键按下
	{
		delay(100);        	//去抖
		if (R != 0x0f)		   // 再次检测，确认有键按下
		{
			R = KEYP & 0x0f; //读入行线值，确认按键所在行  （值为0的位所在的行）
			KEYP = R | 0xf0; //输出当前行线值
			C = KEYP & 0xf0; //读入列线值，确认按键所在列  （值为0的位所在的列）
			switch (R + C)// 行列组合，确认按键所在行列 （值为0的位所在的行列）
			{									// 列  行
			case 0x7e:return(1); break; //1  组合码0x7e=0111 1110 表示按键在1行1列,键号1
			case 0xbe:return(2); break; //2  组合码0xbe=1011 1110 表示按键在1行2列,键号2
			case 0xde:return(3); break; //3
			case 0xee:return(4); break; //4
			case 0x7d:return(5); break; //5
			case 0xbd:return(6); break; //6
			case 0xdd:return(7); break; //7
			case 0xed:return(8); break; //8
			case 0x7b:return(9); break; //9
			case 0xbb:return(10); break; //A
			case 0xdb:return(11); break; //B
			case 0xeb:return(12); break;//C
			case 0x77:return(13); break;//D
			case 0xb7:return(14); break;//E
			case 0xd7:return(15); break;//F
			case 0xe7:return(16); break;//H组合码0xe7=1110 0111 表示按键在4行4列,键号H
			}
		}
	}
	return(0);     //无键按下返回0
}

/* 主函数 这里仅用来测试按键功能并显示按键号 */
void main()
{
	while (1)   				// 循环
	{
		K = keyRC();   			// 读取键值到K（全局变量）
		if (K)P2 = LED[K];		// 若有键按下，通过P2口的LED显示键号
	}
}
/* 延时函数 */
void delay(int ms)
{
	unsigned int i = ms * 91;
	for (; i > 0; i--) { ; }
}
