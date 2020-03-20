#include <reg51.h>
#define uchar unsigned char
#define KEYP P1  // ָ��������ʹ�õĶ˿�
uchar LED[17] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0xf6 };
// LED�������ʾ����0-F�Ķ���
uchar K;	// ȫ�ֱ���
void delay(int ms); // ������ʱ����
/*************** ���о��󰴼�ɨ�躯�� *********************
*�������ܣ����ʶ�����ӵ�KEYP���ϵ�16��������P.7-P.4 Ϊ�У� P.0-P.3Ϊ��
*��������ֵ�����������µļ���1-9��A-H��������0��ʾ�޼�����
********************************************************** */
uchar keyRC(void)
{
	uchar R;			//��ֵ
	uchar C;			//��ֵ
	KEYP = 0x0f;     //4���������0000,������� 1111
	R = KEYP & 0x0f;   //��������ֵ
	if (R != 0x0f)    	//������ֵ��Ϊ1111������⵽�м�����
	{
		delay(100);        	//ȥ��
		if (R != 0x0f)		   // �ٴμ�⣬ȷ���м�����
		{
			R = KEYP & 0x0f; //��������ֵ��ȷ�ϰ���������  ��ֵΪ0��λ���ڵ��У�
			KEYP = R | 0xf0; //�����ǰ����ֵ
			C = KEYP & 0xf0; //��������ֵ��ȷ�ϰ���������  ��ֵΪ0��λ���ڵ��У�
			switch (R + C)// ������ϣ�ȷ�ϰ����������� ��ֵΪ0��λ���ڵ����У�
			{									// ��  ��
			case 0x7e:return(1); break; //1  �����0x7e=0111 1110 ��ʾ������1��1��,����1
			case 0xbe:return(2); break; //2  �����0xbe=1011 1110 ��ʾ������1��2��,����2
			case 0xde:return(3); break; //3
			case 0xee:return(4); break; //4
			case 0x7d:return(5); break; //5
			case 0xbd:return(6); break; //6
			case 0xdd:return(7); break; //7
			case 0xed:return(8); break; //8
			case 0x7b:return(9); break; //9
			case 0xbb:return(10); break; //A
			case 0xdb:return(11); break; //B
			case 0xeb:return(12); break;//C
			case 0x77:return(13); break;//D
			case 0xb7:return(14); break;//E
			case 0xd7:return(15); break;//F
			case 0xe7:return(16); break;//H�����0xe7=1110 0111 ��ʾ������4��4��,����H
			}
		}
	}
	return(0);     //�޼����·���0
}

/* ������ ������������԰������ܲ���ʾ������ */
void main()
{
	while (1)   				// ѭ��
	{
		K = keyRC();   			// ��ȡ��ֵ��K��ȫ�ֱ�����
		if (K)P2 = LED[K];		// ���м����£�ͨ��P2�ڵ�LED��ʾ����
	}
}
/* ��ʱ���� */
void delay(int ms)
{
	unsigned int i = ms * 91;
	for (; i > 0; i--) { ; }
}
