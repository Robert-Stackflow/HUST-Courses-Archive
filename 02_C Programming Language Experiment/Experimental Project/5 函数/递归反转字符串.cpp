#include<stdio.h>
void myrever(void)
{
	char c;
	c=getchar();
	if (c!='\n')
	{
		myrever();
		putchar(c);
	}
	
}
int main(void)
{
	myrever();
	return 0;
} 
