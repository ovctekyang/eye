#include <reg51.h>
#define uchar unsigned char 
#define uint unsigned int  
uint X = 0;			   // 计数变量X
char buff[8];		 // 声明显示缓冲数组（存放待显示的8个数字）
void D2BUFF(uint D);	   	// 声明将数据拆送数据缓冲的函数
void DISP(uchar* buff);	  	 // 声明8位LED显示函数DISP()
sbit IN = P3 ^ 4;		 // 指定信号输入引脚为P3.4
bit IN0;			 // 声明位变量IN0保存引脚IN原状态
void delay(int ms);  // 声明延时函数
void D2BUFF(uint D); // 声明拆送显示缓冲（数组buff）函数 
/* 定义显示函数，动态扫描显示数组buff中的8个数字 */
void DISP(uchar* buff)
{
	uchar code LED[16] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
	0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71 }; // 数字0-F笔划段码
	uchar i = 0;
	P0 = 0;  				// 关显示
	P2 = 1;				// 从最低位P2.1开始扫描
	for (i = 0; i < 8; i++)
	{
		P0 = LED[buff[i]];  // 通过P0口向LED数码管输出第i位数的段码
		delay(5);			// 延时约5毫秒
		P0 = 0;			// 关显示
		P2 = (P2 << 1);		// P2口左移，实现LED逐位扫描显示
	}
}
/* 主函数，调用函数DISP显示引脚上的脉冲计数结果 */
void main()
{
	while (1)
	{
		IN = 1;			   // 输入端置1
		if (IN != IN0) 	   // 如果发生跳变
		{
			IN0 = IN;			   // 保存本次状态
			if (!IN)
			{
				++X;	   // 如果为下跳沿，X+1计数
				D2BUFF(X);       // 计数结果送显示数组
			}
		}
		DISP(buff);			// 调用disp函数显示计数结果
		delay(10);			// 延时
	}
}
/* 将数D的各位拆送显示缓冲（数组buff）函数 */
void D2BUFF(uint D)
{
	uint X;
	uchar i;
	X = D;
	for (i = 0; i < 5; i++)	  // 对整形数逐位分离(<65536)需要分离5次
	{
		buff[i] = X % 10;	 // 取最低位数字存入数组元素buff[i]
		X = X / 10;		 // 舍去最低位数字
	}
}
/* 延时函数，入口参数ms为延时的毫秒数 */
void delay(int ms)
{
	unsigned int i;
	for (i = ms * 91; i > 0; i--)  // 每次循环用时是一定的，根据参数ms确定循环次数达到延时
	{
		;
	}
}