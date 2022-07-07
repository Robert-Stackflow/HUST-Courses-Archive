#include <stdio.h>
short p[] = { 0x10, 0x20, 0x70, 0x80 };
int main(int argc, char* argv[])
{
	int flag=0;
	int  x = -1;
	int  y = 3;
	if (x > y)
		flag = 1;

	flag = (x > y) ? 10 : 20;

	printf("%d %d \n", x, y);
	x = x - y;
	y = x + y;
	x = y - x;
	printf("%d %d \n", x, y);
	x = x^y;
	y = x^y;
	x = x^y;
	printf("%d %d \n", x, y);
	return 0;
}
