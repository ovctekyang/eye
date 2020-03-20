#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit ir = P3 ^ 2;
sbit dula = P2 ^ 6;
sbit wela = P2 ^ 7;
uchar code table_du[] = {
    0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F,0X77,0X7C,0X39,0X5E,0X79,0X71
};
uchar code table_we[] = {
    0XFE,0XFD,0XFF,0XFF,0XEF,0XDF
};

uchar irtime;
uchar irdata[33];
uchar bitnum;
uchar startflag;
uchar irok;
uchar ircode[4];
uchar irprosok;
uchar disnum[8];
 
void timer0init(void)
{
    TMOD = OX02;
    TH0 = 0X00;
    TL0 = 0X00;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void irpros(void)
{
    uchar num, k, i;
    k = 1;
    for ( j = 0; j < 4; j++)
    {
        for (i = 0; i < 8; i++)
        {
            num = num >> 1
                if (irdata[k] > 6)
                {
                    num = num | 0x80;
                }
            k++;
        }
        ircode[j] = num;
    }
    irprosok = 1;
}

void irwork(void)//对红外码值进行转换
{
    disnum[0] = ircode[0] / 16;
    disnum[1] = ircode[0] % 16;
    disnum[2] = ircode[1] / 16;
    disnum[3] = ircode[1] % 16;
    disnum[4] = ircode[2] / 16;
    disnum[5] = ircode[2] % 16;
    disnum[6] = ircode[3] / 16;
    disnum[7] = ircode[3] % 16;
}

delay(uchar x)
{
    uchar a, b;
    for (a = x; a > 0; a--);
        for (b = 200; b > 0; b--);
}

display()
{
    uchar i;
    for ( i = 0; i < 6; i++)
    {
        P0 = 0XFF;
        wela = 1;
        wela = 0;
        P0 = table_du[disnum[i]];
        dula = 1;
        dula = 0;
        P0 = table_we[i];
        wela = 1;
        wela = 0;
        delay(10);
    }
}

void int0init(void)
{
    IT0 = 1;
    EX0 = 1;
    EA = 1;
}

void main()
{
    timer0init();
    int0init();
    while (1)
    {
        if (irok == 1)
        {
            irpros();
            irok = 0;
        }
        if (irprosok==1)
        {
            irwork();
            irprosok = 0;
        }
        display();
    }
}

void int0() interrupt 0
{
    if (startflag)
    {
        if (irtime > 32 && irtime < 63)
        {
            bitnum = 0;
        }
        irdata[bitnum] = irtime;
        irtime = 0;
        bitnum++;
        if (bitnum == 33)
        {
            bitnum = 0;
            irok = 1;
        }
    }
    else
    {
        irtime = 0;
        startflag = 1;
    }
}

void timer0() interrupt 1
{
    irtime++;
}