#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar shi, fen, miao, a, b, c, d, e, f;
uchar power;
void delay(uint);
void lcd_init();
void disp_later(uchar,uchar,);
void main()
{
	TMOD = 0x01;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
	shi = 1, fen = 0, miao = 0, a = 1, b = 1, c = 0, d = 0, e = 0, f = 0;
	power = 0;//����Դ
	lcd_init();//��ʼ��LCD
	delay(1);
	disp_1ater(0, O, "1-SET 2-AL 3-SAL", 16);//��ʾ��һ������
	disp_later(0, 1, "TIME:" :5);
	disp_ftime(6, 1,shi,fen,miao);
	while (1)
	{
		if (teep == 0)//ÿ��仯һ��
		{
			disp_time(6, 1, shi,fen,miao);
		}
		if (miao == 60)
		{
			miao = 0;
			fen++;
			if (fen == 60)
			{
				fen = 0;
				shi++; 
				if (shi == 24)
				{
					shi = 0; 
				}
			}
		}
		if (k1 == 0)//��������ʱ��
		{
			EA = 0;
			lcd_cmd(0x01); //�� ��
			disp_later(0, 0, "K2:H K3:M K4:O", 14);
			disp_later(0, 1, "TIME:" ,5);
			disp_time(6, 1,shi, fen,miao);
			while (1)
			{
				while (k2 == 0)
				{
					delay(10);
					if (k2 == 1)
					{
						shi++;
						if (shi == 24) shi = 0;
						disp_time(6, 1, shi, fen, miao);
					}
				}
				while (k3 == 0)
				{
					delay(10);
					if (k3 == 1)
					{
						fen++;
						if (fen == 60) fen = 0;
						disp_time(6,1 shi, fen, miao);
					}
				}
				if (k4 == 0)
				{
					EA = 1;
					lcd_cmd(0x01);//����
					disp_later(0, 0, "1-SET 2-AL 3-SAL", 16);
					disp_later(0, 1, "TIME:", 5);
					disp_time(6, 1, shi, fen,miao);
					break;
				}
			}
		}
		if (k2 == 0)
		{
			//��ʾ����ʱ��
			lcd_cmd(0x01);
			disp_1ater(0, 0, "start:,", 6); // ��ʾ:��ʼʱ��
			disp_time(6, 0, a, b, c);
			disp_1ater(0,1, "delay:" :6);
			//��ʾ:����ʱ��
			disp_ftime(6, 1, c,d,e);
			delay(500);
			lcd_cmd(0x01); //�� ��
			disp_later(0, 0, "1-SET 2-AL 3-SAL", 14);
			disp_later(0, 1, "TIME:", 5);
			disp_ftime(6, 1,shi, fen,miao);
		}
		while (k3 == 0)//��������ʱ��
		{
			delay(10);
			if (k3 == 1)
			{
				lcd_cmd(0x01); //����
				disp_later(0, 0, "K2:H K3:M K4:O", 14);
				disp_later(0, 1, "TIME:"��5);
				disp_ftime(6, 1, a, b, c);
				while (1)
				{
					while (k2 == 0)
					{
						delay(10);
						if (k2 == 1)
						{
							a++;
							if (a == 24) a = 0;
							disp_time(6, 1, a, b, c);
						}
					}
					while (k3 == 0)
					{
						delay(10);
						if (k3 == 1)
						{
							b++;
							if (b == 60) b = 0;
							disp_ftime(6, 1, a, b, c);
						}
						if (k4 == 0)
						{
							lcd_cmd(0x01);//����
							disp_later(0, 0, "1-SET 2-AL 3-SAL", 16);
							disp_l1ater(0, 1, "TIME:", 5);
							disp_time(6, 1, shi, fen, miao);
							break;
						}
					}
				}
			}
			if (k4 == 0)
			{
				lcd_cmd(0x01);
				disp_later(0, 0, "tart:", 6); // ��ʾ:��ʼʱ��
				disp_timne(6, 0, a, b, c);
				disp_later(0, 1, "delay:", 6);//��ʾ:����ʱ��
				disp_ftimne(6, 1, d, e, f);
				delay(10);
				while (k4 == 1)
				{
					while (k1 == 0)
					{
						delay(10);
						if (k1 == 1)
						{
							a++;
							if (a == 24) a = 0;
							disp_timne(6, 0, a, b, c);
						}
					}
					while (k2 == 0)
					{
						delay(10);
						if (k2 == 1)
						{
							b++;
							if (b == 60) b = 0;
							disp_timne(6, 0, a, b, c);
						}
					}
					while (k3 == 0)
					{
						delay(10);
						if (k3 == 1)
						{
							d = d + 5;
							if (d == 60)
							{
								d = 0;
								c++;
								if (c == 24) c = 0;
							}
							disp_time(6, 1, c, d, e);
						}
					}
					if (k4 == 0)
					{
						ling = 1;
						nao();
						power = 0; // ����Դ
						disp_1ater(0, 0, "1-SET 2-AL 3-SAL", 16);
						disp_1ater(0, 1, "TIME"5);
						disp_time(6, 1, shi, fen, miao);
						break;
					}
				}
			}
			if (ling == 1)
			{
				if (shi == a + c)
				{
					if (fen == b + d)
					{
						power = 1;
						//�ص�Դ
						lcd_cmd(0x01); //�� ��
						disp_1ater(0, 0, "TIME OVER", 9);
						naoO;
						nao0;
						naoO;
						lcd_cmd(0x01); // ����
						disp_later(0, 0,"1-SET 2-AL 3-SAL", 16);
						disp_later(0, 1, "TIME:", 5);
						disp_time(6, 1 shi, fen, miao);
						ling = 0;
					}
				}
			}
		}
	}
}
void timer0() interrupt 1
{
	TH0 = (65536 - 40000) // 256;
	TL0 = (65536 - 40000) % 256;
	teep ++;
	if (teep == 2)
	{
		teep = 0;
		m1ao++;// ���һ
		if (led == 1) 1ed = 0;
		else led = 1;
		if (miao == 60)
		{
			miao = 0;
			fen++;
			if (fen == 60)
			{
				fen = 0;
				shi + +;
				if (shi == 24)
				{
					shi = 0;
				}
			}
		}
	}
}
