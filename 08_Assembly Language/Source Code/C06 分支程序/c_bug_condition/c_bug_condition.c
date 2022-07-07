#include <stdio.h>
int sum(int a[], unsigned length)
{
	int i;
	int result = 0;
//	for (i = 0; i <= length - 1; i++)
//		result += a[i];
	for (i = 0; i < length ; i++)
		result += a[i];

	return result;
}
int main(int argc, char* argv[])
{
	int  a[5] = { 1, 2, 3, 4, 5 };
	short x =  100;
	short y = -32700;
	short z;
	z = sum(a, 0);
	printf("sum : %d \n", z);
	if (x < y)
		printf("condition1:  %d < %d \n", x, y);
	z = x - y;
	if (z  < 0)
		printf("condition2:  %d < %d \n", x, y);
	return 0;
}