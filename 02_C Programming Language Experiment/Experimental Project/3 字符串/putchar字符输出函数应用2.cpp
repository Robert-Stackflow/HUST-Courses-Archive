#include<stdio.h>
int main(void)
{
	char c1,c2='a',c3,c4,c5;
	c1='a';
	c3=97;
	c4='\141';//代表八进制 
	c5='\x61';//代表十六进制 
	//可以输出ASCII码，或者字符 
	putchar(c1);
	putchar(c2);
	putchar(c3);
	putchar(c4);
	putchar(c5); 
	return 0; 
}
