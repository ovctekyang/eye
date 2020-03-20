#include<reg51.h>
sbit P30 = P3 ^ 0;
void main()
{
	TMOD = 0x01;
	TH0 = 0xfe;
	TL0 = 0x0c;
	TR0 = 1;
	while (1)
	{
		if (TF0)
		{
			TF0 = 0;
			TH0 = 0xfe;
			TL0 = 0x0c;
			P30 = ~P30;
		}
	}
}