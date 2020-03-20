#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
//晶振频率fosc=12MHZ，所以系统周期T=1us
uchar adj=100;	    // 频率调节增量
sbit output=P3^0;   //方波输出端口
uint freq;				  // 设定频率值
uchar T0_H,T0_L;  //定时器0的定时初值高低字节
/* 主程序 */
void main(void)
{
	freq=1000; 
	TMOD=0x01;  // T0 定时方式1 
	//定时器初始值=65536-(t/2)/T=65536-1000000/(freq*2) 
	T0_H=(65536-1000000/(freq*2))/256;
	T0_L=(65536-1000000/(freq*2))%256;
	TL0=T0_L;
	TH0=T0_H;
	EA=1;      //开总中断
	ET0=1;     //开T0中断
	EX0=1;     //开INT0中断
	EX1=1;     //开INT1中断
	IT0=1;     //设置外部中断INT0为下降沿触发
	IT1=1;     //设置外部中断INT1为下降沿触发
	PT0=1;     //设置T0中断为高优先级中断
	TR0=1;   	// 启动T0
	while(1);	// 等中断
}

//T0中断
void T0_freq() interrupt 1
{
	output=~output;  //输出变反，产生方波
	TL0=T0_L;  // 重设初值
	TH0=T0_H;
}

 //INT0中断
void freq_inc() interrupt 0
{
 freq=freq+adj;  // 频率增加Δf
 T0_H=(65536-1000000/(freq*2))/256; // 重新计算初值
 T0_L=(65536-1000000/(freq*2))%256;
}
//INT1中断
void freq_dec() interrupt 2
{
 freq=freq-adj;  // 频率减少Δf
 T0_H=(65536-1000000/(freq*2))/256; // 重新计算初值
 T0_L=(65536-1000000/(freq*2))%256;
}