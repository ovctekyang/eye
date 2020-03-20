#include<reg51.h>
sbit K1 = P1 ^ 0;
sbit K2 = P1 ^ 1;
sbit K3 = P1 ^ 2;
sbit GREEN = P3 ^ 0;
sbit YELLOW = P3 ^ 1;
sbit RED = P3 ^ 2;
void main()
{
	while (1)
	{
		GREEN = K1 && K2 && K3;
		RED = !(K1 || K2 || K3);
		YELLOW = !(GREEN || RED);
	}
}