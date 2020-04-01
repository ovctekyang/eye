#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
uchar num,disnum;
uchar code table_du[]={ 0x3f,0x06,0x5b,
0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,
0x7c,0x39,0x5e,0x79,0x71 };


display(uint);
delay(uchar);

void main()
{
	
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
			if(disnum==1000)
			disnum=0;
			disnum++;	
		}
		display(disnum);
	}
}


void time0() interrupt 1 
{
	TH0=(65536-50000)/256; 
	TL0=(65536-50000)%256;
	num++;
}

display(uint disnum)  
{
	
	P0=table_du[disnum/100];
	dula=1;
	dula=0;
	P0=0xfe;
	wela=1;
	wela=0;
	delay(10);

	P0=table_du[disnum%100/10];
	dula=1;
	dula=0;
	P0=0xfd;
	wela=1;
	wela=0;
	delay(10);

	P0=table_du[disnum%100%10];
	dula=1;
	dula=0;
	P0=0xfb;
	wela=1;
	wela=0;
	delay(10);
}

delay(uchar x)
{
	uchar a,b;
	for(a=x;a>0;a--)
		for(b=200;b>0;b--);
}
