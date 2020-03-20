#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define DATA_PORT P0
//-------------------------------------------
//              管脚定义   
//------------------------------------------
sbit RS = P2 ^ 0;     //数据(L)/命令(H)选择
sbit LCDRW = P2 ^ 1;     //写，低电平有效
sbit EN = P2 ^ 2;     //使能,低电平有效
//===========================================
//              函数声明
//-------------------------------------------
void delay_lcd(char);
void write_data(char);
void write_com(char);
void lcd_init();
void delay_ms(char);
void print_string(char*);
//--------------------------------------------
//              写数据函数
//--------------------------------------------
void write_data(char dat) {
	RS = 1;          //数据
	LCDRW = 0;        //写
	DATA_PORT = dat; //把数据送到P口
	delay_ms(5);      //当晶振较高时加延时
	EN = 1;
	delay_ms(5);    //当晶振较高时加延时
	EN = 0;          //关使能
}
//--------------------------------------------
//              写命令函数
//--------------------------------------------
void write_com(char com) {
	RS = 0;          //命令
	LCDRW = 0;        //写
	DATA_PORT = com;
	delay_ms(5);    //当晶振较高时加延时
	EN = 1;
	delay_ms(5);    //当晶振较高时加延时
	EN = 0;
}
//--------------------------------------------
//        1602初始化函数
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
//              延时函数
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