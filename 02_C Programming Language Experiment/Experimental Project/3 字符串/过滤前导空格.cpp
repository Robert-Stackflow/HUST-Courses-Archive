#include<stdio.h> 
int main(void)
{
	char c;
	while((c=getchar())!=EOF)
	{
		if(c==EOF) break;
		else if(c!=' ') 
		    putchar(c);
	}
	return 0;
}
