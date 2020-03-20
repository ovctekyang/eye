#include<pub.h>
void main()
{
	unsigned int i;
	TMOD = 0x05;
	TH0 = 0;
	TL0 = 0;
	TR0 = 0;
	while (1)
	{
		i = TH0 * 256 + TL0;
		disp(i);
	}
}