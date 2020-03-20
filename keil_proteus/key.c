#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define KEYP P1  // ָ��������ʹ�õĶ˿�
// LED�������ʾ����0-F�Ķ�������
uchar LED[17] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,
0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0xf6 };
uchar K;	// ȫ�ֱ���������
void delay(int ms);  // ������ʱ����
/*********����ɨ�躯�� ***************
*�������ܣ����KEYP.0-KEYP.3�ϵ��ĸ�����
*��������ֵ�����������µļ��ţ����������+4��������0��ʾ�޼�����
************************************ */
uchar keyscan()
{
	uchar K = 0;	// ����(�ֲ�����K)
	uint i = 0;
	uchar KPS; 					// �����˿�״̬ 
	KPS = KEYP & 0x0f; // ��ȡKEYP�ڵ�4λ��KPS
	if (KPS != 0x0f) // �粻����0x0f����ʾ�м�����
	{
		delay(20);	// ��ʱ20ms����������������
		if ((KEYP & 0x0f) == KPS)  // �ٴζ�ȡKEYP �ڵ�4λ������ΪKPS����ʾ�ü�ȷ����
		{
			for (i = 0; (KEYP & 0x0f) == KPS; i++)
				// �ȴ������ͷţ��ͷź��ٵ���KPS��
			{
				switch (KPS)	 //ת��Ϊ����
				{
				case 0x0e:K = 1; break;
				case 0x0d:K = 2; break;
				case 0x0b:K = 3; break;
				case 0x07:K = 4; break;
				}
			}
			if (i > 10000)K += 4;    // ����������ֵ+4, 	}
		}
		return(K);	// ���ؼ��ţ�0��ʾ�޼�����
	}
}

/* ������ */
void main()
{
	while (1)   		// ѭ��
	{
		K = keyscan();   	// ��ȡ��ֵ��K��ȫ�ֱ�����
		if (K != 0)	P2 = LED[K];		// ͨ��P2�ڵ�LED��ʾ���صļ���
	}
}
/* ��ʱ���� */
void delay(int ms)
{
	unsigned int i = ms * 91;
	for (; i > 0; i--) { ; }
}