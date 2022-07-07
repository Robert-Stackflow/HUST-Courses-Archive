#include <stdio.h>
int main(int argc, char* argv[])
{
	short x = -1;
	unsigned short y = -1;
	printf("%d %d \n", x, y);
	if (x > 0)  printf("x is positive\n");
	if (y > 0) printf("y is positive\n");
	return 0;
}