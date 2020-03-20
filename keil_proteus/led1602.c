#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[] = "MY QQ NUMBER";
uchar code table1[] = "799974296";
uchar temp;
sbit lcden = P3 ^ 4;
sbit lcdrs = P3 ^ 5;
sbit duan = P2 ^ 6;
sbit wei = P2 ^ 7;
void delay(uint xms)
{
    uint i, j;
    for (i = 0; i < xms; i++)
        for (j = 0; j < xms; j++);
}
void write_com(uchar com)//��ʼ��д����
{
    lcdrs = 0;
    P0 = com;
    delay(5);
    lcden = 1;
    delay(5);
    lcden = 0;
}
void write_date(uchar date)//��ʼ��д����
{
    lcdrs = 1;
    P0 = date;
    delay(5);
    lcden = 1;
    delay(5);
    lcden = 0;
}
void init()
{
    duan = 0;
    wei = 0;
    lcden = 0;
    write_com(0x38); //��ʾģʽ������
    write_com(0x0e);  //����Ϊ����ʾ����ʾ��꣬��겻��˸
    write_com(0x06);  //д��һ���ַ����ַָ��͹���һ��������ʾ���ƶ�
    write_com(0x01);//��ʼ����ʱ��������
    write_com(0x40);  //������ָ���ƶ�����һ�е�һ��
}
void main()
{
    init();
    write_com(0x40 + 0x53);//��ʼд��λ�ù������Ա��ƶ�
    for (temp = 0; temp < 12; temp++)
    {
        write_date(table[temp]);
        delay(20);
    }
    write_com(0x80 + 0x53);//�л����ڶ���
    for (temp = 0; temp < 9; temp++)
    {
        write_date(table1[temp]);
        delay(20);
    }
    for (temp = 0; temp < 19; temp++)
    {
        write_com(0x18);
        delay(200);
        /*
        ���ڹ�곣�õļ���ָ��
        0x10�ַ��������������һ��λ��
        0x14�ַ��������������һ��λ��
        0x18�ַ��͹��һ������һ��λ��
        0x1c�ַ��͹��һ������һ��λ��
        */
    }
    while (1);
}