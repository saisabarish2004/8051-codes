#include<reg51.h>
sbit led = P2^1;
void delay();
void main()
{

	while(1)
	{
	led=1;
	delay();
	led=0;
	delay();
	}
}
void delay()
{

	TMOD=0x10;
	TR1=1;
	TH1=0x4b;
	TL1=0xfd;
	
	while(TF1=0);
	TR1=0;
	TF1=0;
}