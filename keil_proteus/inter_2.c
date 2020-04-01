#include <reg52.h>
unsigned char a,num;
sbit LED1=P0^0;

void main()
{
	num=0;
	EA=1;
	ET0=1;
	TMOD=0X01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TR0=1;
	while(1)
	{
		if(num==20)
		{
			num=0;
			LED1=~LED1;
		}
	}
}


void time0() interrupt 1 
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;
}
