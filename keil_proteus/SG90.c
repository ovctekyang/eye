#include <reg51.h>      
#include <math.h>
typedef unsigned char uchar;
typedef unsigned int uint;
sbit  KEY1 = P3 ^ 4;					//����1
sbit  KEY2 = P3 ^ 5;					//����2
sbit PWM_OUT = P2 ^ 7;				//PWM�����
uint PWM_Value;			//����pwmֵ
uchar order = 0;
void Delay(unsigned int s);      //��ʱ��������
uchar flag;									//���������־
/*��ʱ����*/
void Delay(unsigned int s)
{
    unsigned int i;
    for (i = 0; i < s; i++);
    for (i = 0; i < s; i++);
}
/*��ʱ����ʼ��*/
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
/*������*/
void main(void)
{
    Delay(6000);
    PWM_Value = 1500;					//pwm��ֵΪ1500
    Init_Timer0();
    while (1)
    {
        if ((KEY1 == 0) | (KEY2 == 0))							//����1�򰴼�2������
        {
            if (KEY1 == 0)												//ȷ�ϰ���1������
            {
                flag = 1;												//��־λ��ֵ1
            }
            if (KEY2 == 0)									//ȷ�ϰ���2������
            {
                flag = 2;											//��־λ��ֵ2
            }
        }
        else
        {
            flag = 0;								//�����־λΪ0
        }
        Delay(20);								//��ʱ20ms
    }
}
/*****�жϳ���*******/
void timer0(void) interrupt 1
{
    if (flag == 1)	PWM_Value += 1;							//�����־λ1ʱ��pwm��ֵ��1
    if (flag == 2)	PWM_Value -= 1;							//�����־λΪ2ʱ��pwm��1
    if (PWM_Value >= 2500)										//���pwm��ֵ����2500
        PWM_Value = 2500;												//�򱣳���2500
    if (PWM_Value <= 500)											//���pwm��ֵС��500
        PWM_Value = 500;													//�򱣳���500
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