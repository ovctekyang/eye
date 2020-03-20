#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define DATA_PORT P0
//-------------------------------------------
//              �ܽŶ���   
//------------------------------------------
sbit RS = P2 ^ 0;     //����(L)/����(H)ѡ��
sbit LCDRW = P2 ^ 1;     //д���͵�ƽ��Ч
sbit EN = P2 ^ 2;     //ʹ��,�͵�ƽ��Ч
//===========================================
//              ��������
//-------------------------------------------
void delay_lcd(char);
void write_data(char);
void write_com(char);
void lcd_init();
void delay_ms(char);
void print_string(char*);
//--------------------------------------------
//              д���ݺ���
//--------------------------------------------
void write_data(char dat) {
	RS = 1;          //����
	LCDRW = 0;        //д
	DATA_PORT = dat; //�������͵�P��
	delay_ms(5);      //������ϸ�ʱ����ʱ
	EN = 1;
	delay_ms(5);    //������ϸ�ʱ����ʱ
	EN = 0;          //��ʹ��
}
//--------------------------------------------
//              д�����
//--------------------------------------------
void write_com(char com) {
	RS = 0;          //����
	LCDRW = 0;        //д
	DATA_PORT = com;
	delay_ms(5);    //������ϸ�ʱ����ʱ
	EN = 1;
	delay_ms(5);    //������ϸ�ʱ����ʱ
	EN = 0;
}
//--------------------------------------------
//        1602��ʼ������
//--------------------------------------------
void lcd_init() {
	LCDRW = 0;
	RS = 0;
	write_com(0x36);     //set text home address
	write_com(0x0f);     //display switch,display on,cursor on,blink on.
	write_com(0x38);
	write_com(0x06);     //input set.
	write_com(0x01);     //screen clear
	write_com(0x80);    //DDRAM AD set to 00h,
}
void print_string(char* str) {
	int i;
	for (i = 0; str[i] != 0; i++)
	{
		write_data(str[i]);
		delay_ms(200);
	}
}
//--------------------------------------------
//              ��ʱ����
//--------------------------------------------
void delay_ms(uchar t) {
	int j;
	for (; t != 0; t--)
		for (j = 0; j < 255; j++);

}
main() {
	lcd_init();

	print_string("Hello OVCTEK!");
	write_com(0xc0);    //DDRAM AD set to 00h,
	print_string("This is YXN!");
	while (1);
}