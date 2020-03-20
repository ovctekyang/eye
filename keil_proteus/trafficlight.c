#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit EW_RED = P1 ^ 3;
sbit EW_YELLOW = P1 ^ 2;
sbit EW_GREEN = P1 ^ 1;
sbit SN_RED = P1 ^ 7;
sbit SN_YELLOW = P1 ^ 6;
sbit SN_GREEN = P1 ^ 5;
sbit EW_MAN = P1 ^ 0;
sbit STOP = P3 ^ 2;
char TIME_EW;
char TIME_SN;
void delay(uint ms)
{
	uint i = ms * 91;
	for (; i > 0; i--);
}
void display(uchar bin)
{
	char h, l;
	h = bin / 10;
	l = bin % 10;
	P2 = h * 16 + l;
}
void main()
{
	char i, j;
	while (1)
	{
		STOP = 1;
		while (STOP)
		{
			TIME_EW = 0;
			STOP = 1;
			P1 = 0x82;
			display(TIME_EW);
		}
		delay(20);
		STOP = 1;
		while (!STOP)
		{
			TIME_EW = 10;
			for ( i = TIME_EW; i>=5;i--)
			{
				display(i);
				delay(500);
				P1 = 0x82;
				delay(500);
			}
			for (i = 5; i >= 0; i--)
			{
				display(i);
				P1 = 0x80;
				delay(500);
				P1 = 0x82;
				delay(500);
			}
			for (i = 3; i >= 0; i--)
			{
				display(i);
				P1 = 0x84;
				delay(500);
				delay(500);
			}
			TIME_EW = 20;
			for (j = 5; j >= 0; j--)
			{
				display(j);
				delay(500);
				P1 = 0x28;
				delay(500);
			}
			for (j = 10; j >= 0; j--)
			{
				P1 = 0x08;
				display(j);
				delay(500);
				P1 = 0x28;
				delay(500);
			}
		}
	}
}
