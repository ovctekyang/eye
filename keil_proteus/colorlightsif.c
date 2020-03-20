#include<reg51.h>
sbit P3_7=P3^7;
void main()
{
  while(1)
  {
    if(P3_7)
	P0=0x55;
  }
}


























































 