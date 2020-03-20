#include<reg51.h>
unsigned char a,num;
sbit LED1=P1^0;
unsigned int i,j;

void main()
{
	while (1)
	{
		P1=~(1<<j++);
		if(j==8) j=0;
		for (i = 0; i < 50000; i++);
	}
}
