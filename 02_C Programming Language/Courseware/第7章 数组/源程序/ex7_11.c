#include "stdio.h"
int strlen(char s[]);
int main(void)
{
	char s[]="there is a boat on the lake.";
	printf("%d\n",strlen(s));
	return 0;
}
int strlen(char s[])
{	int j=0;
	while(s[j]!= '\0') j++;  /* ������while(s[j++])����������� */
	return j;
}
