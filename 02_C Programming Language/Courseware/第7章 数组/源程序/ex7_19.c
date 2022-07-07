#include "stdio.h"
#define BASE 10
int atoi(char s[]);
int main(void)
{
	char s[]="12345";
	int x;
	x=atoi(s);
	printf("%d\n",x);
	return 0;
}
int atoi(char s[])
{	int j=0,num=0;
	for(;s[j]!= '\0';j++)
		 num=num*BASE +s[j]- '0';
	return num;
}


