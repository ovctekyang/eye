#include<reg51.h>
#include<intrins.h>
sbit P37 = P3 ^ 7;
void delay(int ms);
void main()
{
	P0 = 0xfe;
	while (1)
	{
		if (P37) P0 = _crol_(P0, 1);
		else P0 = _cror_(P0, 1);
		delay(P1);
	}
}

void delay(int ms)
{
	unsigned int i;
	for (;ms>0; ms--)
	{
		for ( i = 0; i < 124; i++)
		{
			;
		}
	}
}