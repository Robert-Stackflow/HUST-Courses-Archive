#include<stdio.h> 
int main(void)
{
	char c;
	while ((c=getchar())!=EOF){
	if((c>='A')&&(c<='Z'))
		putchar(c+32);
	else 
		putchar(c);
	}
	return 0;
}
