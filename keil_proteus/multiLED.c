#include <reg51.h>
#define uchar unsigned char 
#define uint unsigned int  
uint X = 0;			   // ��������X
char buff[8];		 // ������ʾ�������飨��Ŵ���ʾ��8�����֣�
void D2BUFF(uint D);	   	// ���������ݲ������ݻ���ĺ���
void DISP(uchar* buff);	  	 // ����8λLED��ʾ����DISP()
sbit IN = P3 ^ 4;		 // ָ���ź���������ΪP3.4
bit IN0;			 // ����λ����IN0��������INԭ״̬
void delay(int ms);  // ������ʱ����
void D2BUFF(uint D); // ����������ʾ���壨����buff������ 
/* ������ʾ��������̬ɨ����ʾ����buff�е�8������ */
void DISP(uchar* buff)
{
	uchar code LED[16] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,
	0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71 }; // ����0-F�ʻ�����
	uchar i = 0;
	P0 = 0;  				// ����ʾ
	P2 = 1;				// �����λP2.1��ʼɨ��
	for (i = 0; i < 8; i++)
	{
		P0 = LED[buff[i]];  // ͨ��P0����LED����������iλ���Ķ���
		delay(5);			// ��ʱԼ5����
		P0 = 0;			// ����ʾ
		P2 = (P2 << 1);		// P2�����ƣ�ʵ��LED��λɨ����ʾ
	}
}
/* �����������ú���DISP��ʾ�����ϵ����������� */
void main()
{
	while (1)
	{
		IN = 1;			   // �������1
		if (IN != IN0) 	   // �����������
		{
			IN0 = IN;			   // ���汾��״̬
			if (!IN)
			{
				++X;	   // ���Ϊ�����أ�X+1����
				D2BUFF(X);       // �����������ʾ����
			}
		}
		DISP(buff);			// ����disp������ʾ�������
		delay(10);			// ��ʱ
	}
}
/* ����D�ĸ�λ������ʾ���壨����buff������ */
void D2BUFF(uint D)
{
	uint X;
	uchar i;
	X = D;
	for (i = 0; i < 5; i++)	  // ����������λ����(<65536)��Ҫ����5��
	{
		buff[i] = X % 10;	 // ȡ���λ���ִ�������Ԫ��buff[i]
		X = X / 10;		 // ��ȥ���λ����
	}
}
/* ��ʱ��������ڲ���msΪ��ʱ�ĺ����� */
void delay(int ms)
{
	unsigned int i;
	for (i = ms * 91; i > 0; i--)  // ÿ��ѭ����ʱ��һ���ģ����ݲ���msȷ��ѭ�������ﵽ��ʱ
	{
		;
	}
}