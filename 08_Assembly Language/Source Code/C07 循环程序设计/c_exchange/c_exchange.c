#include <stdio.h>

int main()
{
	register int  a = 20, b = 30;
	printf("%d %d \n", a, b);
	a = (a + b) - (b = a);
	printf("%d %d \n", a, b);
	return 0;
}