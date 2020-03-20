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
void write_com(uchar com)//初始化写命令
{
    lcdrs = 0;
    P0 = com;
    delay(5);
    lcden = 1;
    delay(5);
    lcden = 0;
}
void write_date(uchar date)//初始化写数据
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
    write_com(0x38); //显示模式的设置
    write_com(0x0e);  //设置为开显示，显示光标，光标不闪烁
    write_com(0x06);  //写完一个字符后地址指针和光标加一，整屏显示不移动
    write_com(0x01);//初始化的时候先清屏
    write_com(0x40);  //将数据指针移动到第一行第一个
}
void main()
{
    init();
    write_com(0x40 + 0x53);//起始写的位置光标后移以便移动
    for (temp = 0; temp < 12; temp++)
    {
        write_date(table[temp]);
        delay(20);
    }
    write_com(0x80 + 0x53);//切换到第二行
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
        关于光标常用的几条指令
        0x10字符不动，光标左移一个位置
        0x14字符不动，光标右移一个位置
        0x18字符和光标一起左移一个位置
        0x1c字符和光标一起右移一个位置
        */
    }
    while (1);
}