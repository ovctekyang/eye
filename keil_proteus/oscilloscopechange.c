#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
//����Ƶ��fosc=12MHZ������ϵͳ����T=1us
uchar adj=100;	    // Ƶ�ʵ�������
sbit output=P3^0;   //��������˿�
uint freq;				  // �趨Ƶ��ֵ
uchar T0_H,T0_L;  //��ʱ��0�Ķ�ʱ��ֵ�ߵ��ֽ�
/* ������ */
void main(void)
{
	freq=1000; 
	TMOD=0x01;  // T0 ��ʱ��ʽ1 
	//��ʱ����ʼֵ=65536-(t/2)/T=65536-1000000/(freq*2) 
	T0_H=(65536-1000000/(freq*2))/256;
	T0_L=(65536-1000000/(freq*2))%256;
	TL0=T0_L;
	TH0=T0_H;
	EA=1;      //�����ж�
	ET0=1;     //��T0�ж�
	EX0=1;     //��INT0�ж�
	EX1=1;     //��INT1�ж�
	IT0=1;     //�����ⲿ�ж�INT0Ϊ�½��ش���
	IT1=1;     //�����ⲿ�ж�INT1Ϊ�½��ش���
	PT0=1;     //����T0�ж�Ϊ�����ȼ��ж�
	TR0=1;   	// ����T0
	while(1);	// ���ж�
}

//T0�ж�
void T0_freq() interrupt 1
{
	output=~output;  //����䷴����������
	TL0=T0_L;  // �����ֵ
	TH0=T0_H;
}

 //INT0�ж�
void freq_inc() interrupt 0
{
 freq=freq+adj;  // Ƶ�����Ӧ�f
 T0_H=(65536-1000000/(freq*2))/256; // ���¼����ֵ
 T0_L=(65536-1000000/(freq*2))%256;
}
//INT1�ж�
void freq_dec() interrupt 2
{
 freq=freq-adj;  // Ƶ�ʼ��٦�f
 T0_H=(65536-1000000/(freq*2))/256; // ���¼����ֵ
 T0_L=(65536-1000000/(freq*2))%256;
}