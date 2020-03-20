#include "reg51.h"
#include "intrins.h"
#define uchar unsigned char
void delay(int ms);
sbit P3_7=P3^7;
void main()
{
	unsigned char out=0xfe;
	while(1)
	{
		if(P3_7)
		out=_crol_(out,1);
		else
		out=_cror_(out,1);
		P0=out;
		delay(P1)
	}
}
void delay(int ms)
{
	unsigned int i=ms*91;
	for(;i>0;i--){;}
}