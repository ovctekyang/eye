#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;
sbit wela=P2^7;
uchar num,disnum;
uchar code table_du[]={ 0x3f,0x06,0x5b,
0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,
0x7c,0x39,0x5e,0x79,0x71 };

uchar code table_we[]={
0xfe,0xfd,0xfb,0xf7,0xef,0xdf};


display(uint);
display1(uint);
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
		if(num==1)
		{
			num=0;
			if(disnum==1000)
			disnum=0;
			disnum++;	
		}
		display(disnum);
		//delay(10);
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
	char b3,  b2, b1;            //定义两个有符号整形数b3,b2和b1
	b3=disnum/100;
	b2=(disnum/10)%10;//这里应该这样才对不然会大于10的
	b1=disnum%10;

	P0 = 0xff;
	wela = 1;
	wela = 0;
	P0=table_du[b3];
	dula=1;
	dula=0;
	P0=table_we[0];
	wela=1;
	wela=0;
	delay(10);

	P0 = 0xff;
	wela = 1;
	wela = 0;
	P0=table_du[b2];
	dula=1;
	dula=0;
	P0=table_we[1];
	wela=1;
	wela=0;
	delay(10);

	P0 = 0xff;
	wela = 1;
	wela = 0;
	P0=table_du[b1];
	dula=1;
	dula=0;
	P0=table_we[2];
	wela=1;
	wela=0;
	delay(10);
}
display1(uint disnum)
{
	P0=table_du[disnum%10];
	dula=1;
	dula=0;
	P0=table_we[0];
	wela=1;
	wela=0;
	delay(50);
}

delay(uchar x)
{
	uchar a,b;
	for(a=x;a>0;a--)
		for(b=200;b>0;b--);
}
