#include<stdio.h>
//C语言的大小端问题
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
