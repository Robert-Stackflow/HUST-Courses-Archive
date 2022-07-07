#include "stdio.h"
int strcmp(char s[],char t[]);
int main(void)
{
	char t[80],s[]="there is a boat on the lake.";
	strcpy(t,s);
	printf("%s\n",t);
	return 0;
}
int strcmp(char s[],char t[])
{	int j=0;
	while(s[j]==t[j]&&s[j]!='\0') j++;/*ø…”√while(s[j]==t[j] && s[j])*/
	return s[j]-t[j];
}
