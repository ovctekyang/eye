#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uint disnum,a;
sbit adrd=P3^7;
sbit adwr=P3^6;
sbit dula=P2^6;
sbit wela=P2^7;
uchar code table_du[]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,
0x7d,0x07,0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
delay(uchar);
display(uint);
void main()
{
	while(1)
	{
		wela=1;
		P0=0x7f;
		adwr=1;
		adwr=0;
		adwr=1;

		delay(10);
		
		P1=0xff;
		adrd=1;
		adrd=0;
		disnum=P1;
		adrd=1;
		P1=disnum;
		for(a=20;a>0;a--)
		display(disnum);
	}
}

delay(uchar x)
{
	uchar a,b;
	for(a=x;a>0;a--)
		for(b=200;b>0;b--);

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
