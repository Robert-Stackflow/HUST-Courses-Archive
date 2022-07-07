#include<stdio.h> 
char lower(char c)
{
	char result=c;
	if((c>='A')&&(c<='Z'))
		result=c+32;
	return result;
 } 
int main(void)
{
	char c;
	while ((c=getchar())!=EOF)
		putchar(lower(c));
	return 0;
}
