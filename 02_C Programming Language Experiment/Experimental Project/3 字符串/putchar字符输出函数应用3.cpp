#include<stdio.h>
int main(void)
{
	int i;
	putchar(i=' ');
	putchar(i=32);
	putchar(i=10); //换行符输出 
	putchar(i?'Y':'N');
	//也可以输出表达式的值 
	putchar('\a');//扬声器扬声一次 
	return 0; 
}
