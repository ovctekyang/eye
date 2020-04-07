#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char

uchar code step_table[] = {0x09,0x08, 0x0c, 0x04, 0x06, 0x02, 0x03, 0x01};

void delay(uint t)
{
	while (t--);
}

void main()
{
	uint i;
	while (1)
	{
		for (i = 0; i < 8; i++)
		{
			P1 = step_table[i];
			delay(20000);
		}
	}
}
