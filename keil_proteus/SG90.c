#include <reg51.h>      
#include <math.h>
typedef unsigned char uchar;
typedef unsigned int uint;
sbit  KEY1 = P3 ^ 4;					//按键1
sbit  KEY2 = P3 ^ 5;					//按键2
sbit PWM_OUT = P2 ^ 7;				//PWM输出口
uint PWM_Value;			//定义pwm值
uchar order = 0;
void Delay(unsigned int s);      //延时函数声明
uchar flag;									//舵机按键标志
/*延时函数*/
void Delay(unsigned int s)
{
    unsigned int i;
    for (i = 0; i < s; i++);
    for (i = 0; i < s; i++);
}
/*定时器初始化*/
void Init_Timer0()
{
    TMOD = 0x11;
    TH0 = (65536 - 1500) / 256;
    TL0 = (65536 - 1500) % 256;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
    PT0 = 1;
}
/*主函数*/
void main(void)
{
    Delay(6000);
    PWM_Value = 1500;					//pwm初值为1500
    Init_Timer0();
    while (1)
    {
        if ((KEY1 == 0) | (KEY2 == 0))							//按键1或按键2被按下
        {
            if (KEY1 == 0)												//确认按键1被按下
            {
                flag = 1;												//标志位赋值1
            }
            if (KEY2 == 0)									//确认按键2被按下
            {
                flag = 2;											//标志位赋值2
            }
        }
        else
        {
            flag = 0;								//否则标志位为0
        }
        Delay(20);								//延时20ms
    }
}
/*****中断程序*******/
void timer0(void) interrupt 1
{
    if (flag == 1)	PWM_Value += 1;							//如果标志位1时，pwm的值加1
    if (flag == 2)	PWM_Value -= 1;							//如果标志位为2时，pwm减1
    if (PWM_Value >= 2500)										//如果pwm的值大于2500
        PWM_Value = 2500;												//则保持在2500
    if (PWM_Value <= 500)											//如果pwm的值小于500
        PWM_Value = 500;													//则保持在500
    switch (order)
    {
    case 1:PWM_OUT = 1;
        TH0 = (65536 - PWM_Value) >> 8;
        TL0 = (uchar)(65536 - PWM_Value);
        break;
    case 2:PWM_OUT = 0;
        TH0 = (65536 - (5000 - PWM_Value)) >> 8;
        TL0 = (uchar)(65536 - (5000 - PWM_Value));
        break;
    case 3:
        TH0 = 60536 >> 8;
        TL0 = (uchar)60536;
        break;
    case 4:
        TH0 = 60536 >> 8;
        TL0 = (uchar)60536;
        order = 0;
        break;
    default: order = 0;
        break;
    }
    order++;
}