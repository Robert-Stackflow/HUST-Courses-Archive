#include<stdio.h>
//C���ԵĴ�С������
typedef union chi{
	int i;
	char ch[sizeof(int)];
}CHI;
int main(void)
{
	CHI change;
	change.i=1234;
	for(int i=0;i<sizeof(int);i++)
		printf("%#x ",change.ch[i]);
}
