#include<stdio.h>
int strlen(char s[]) 
{
	int i=0;
	while(s[i++]!='\0');
	return i;
}
int main(void)
{
	printf("\t����Ϊ%d\a",strlen("world!"));
	return 0;
 } 
