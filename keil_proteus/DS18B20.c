#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit ds = P2 ^ 2;
bit flag;
sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;
uchar code table_du[] = {
0x3f,0x06,0x5b,0x4f,0x66,0x6d,
0x7d,0x07,0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71 };

uint temp;

delay(uchar x)
{
	uchar a, b;
	for (a = x; a > 0; a--)
		for (b = 200; b > 0; b--);

}

void delayus(uint t)
{
	while (t--);
}

void ds_reset()//单总线初始化
{
	ds = 1;
	delayus(5);
	ds = 0;
	delayus(80);
	ds = 1;
	delayus(14);
	if (ds == 0)
		flag = 1;
	else
		flag = 0;
	delayus(20);
}

bit ds_read_bit()
{
	bit dat;
	ds = 0;
	_nop_();//1us
	_nop_();//1us
	ds = 1;
	_nop_();
	dat = ds;
	delayus(10);
	return dat;
}

uchar ds_read_byte()
{
	uchar i, j, k;
	for (i = 0; i < 8; i++)
	{
		j = ds_read_bit();
		k = (j << 7) | (k >> 1);
	}
}

void ds_write_byte(uchar dat)
{
	uchar i;
	for ( i = 0; i < 8; i++)
	{
		ds = 0;
		_nop_();
		ds = dat & 0x01;
		delayus(6);
		ds = 1;
		dat = dat >> 1;
	}
	delayus(6);
}

uint read_temperature()
{
	uchar a, b;
	ds - reset();
	ds_write_byte(0xcc);
	ds_write_byte(0xbe);
	a=ds_read_byte();
	b=ds_read_byte();
	temp = b;
	temp = temp << 8;
	temp = temp | a;
	temp = temp * 0.625 * 10 + 0.5;
	return temp;
}

display(uint temp)
{

	P0 = table_du[temp / 100];
	dula = 1;
	dula = 0;
	P0 = 0xfe;
	wela = 1;
	wela = 0;
	delay(10);

	P0 = table_du[temp % 100 / 10] | 0x80;//显示小数
	dula = 1;
	dula = 0;
	P0 = 0xfd;
	wela = 1;
	wela = 0;
	delay(10);

	P0 = table_du[temp % 100 % 10];
	dula = 1;
	dula = 0;
	P0 = 0xfb;
	wela = 1;
	wela = 0;
	delay(10);
}

void main()
{
	while (true)
	{
		ds_reset();
		ds_write_byte(0xcc);
		ds_write_byte(0x44);
		display(read_temperature());
	}
}