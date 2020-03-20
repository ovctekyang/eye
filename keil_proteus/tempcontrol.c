#include "reg51.h"
#define PreT 10
void main()
{
	P0 = (P1 == PreT) ? 0x7f : ((P1 < PreT) ? 0xc7 : 0xf8);
}