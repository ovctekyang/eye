#include"reg51.h"
#define uchar unsigned char
#define uint unsigned int
sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;
sbit led = P0;
uint num;
void delay(uint);

void main()
{
	num = 0;
	EA = 1;
	ET0 = 1;
	TMOD = 0x01;
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	TR0 = 1;
	while (1)
	{
		if (num == 20)
		{
			num = 0;
			led = ~led;
		}
	}
}

void time0() interrupt 1
{
	TH0 = (65536 - 50000) / 256;
	TL0 = (65536 - 50000) % 256;
	num++;
}
void delay(uint ms)
{
	uint i = ms * 91;// 12MHZµÄ¾§Õñ ??
	for (; i > 0; i--);
}