#include<reg51.h>
void main()
{
	char a[10]={1,2,3,4,5,6,7,8,9,0};
	int i;
	SCON=0x50;
	TMOD=0x20;
	TH1=0xFD;
	TR1=1;
	for(i=0;i<=10;i++)
		{
		TR1=1;	
	SBUF=a[i];
		}
	while(TI==0);
	TI=0;
	while(RI==0);
	RI=0;
	}
