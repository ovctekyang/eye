#include"reg51.h"
#define uchar unsigned char
#define uint unsigned int
sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;
uchar table[] = { 0x3f,0x06,0x5b,
0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,
0x7c,0x39,0x5e,0x79,0x71 };
void delay(uint);

void main()
{
	//while (1)
	//{
	//	P0 = 0xea;
	//	wela = 1;
	//	wela = 0;
	//	P0 = table[2];
	//	dula = 1;
	//	dula = 0;
	//	delay(1000);
	//	P0 = table[3];
	//	dula = 1;
	//	dula = 0;
	//	delay(1000);
	//}
	uint i;
	for(i=0;i<16;i++)
	{
		P0 = ~(1<<i);
		wela = 1;
		wela = 0;
		P0 = table[2];
		dula = 1;
		dula = 0;
		delay(1000);
		P0 = table[3];
		dula = 1;
		dula = 0;
		delay(1000);
	}
}
void delay(uint ms)
{
	uint i = ms * 91;// 12MHZµÄ¾§Õñ ??
	for (; i > 0; i--);
}