#include <stdio.h>
unsigned char x[] = {1,2,7,8};
char *p;
int  xxx[10];
int  array[3][5];

int main(int argc, char* argv[])
{
	int  eax;
	int  _ebx;
	short xs = -1;
	unsigned short uy = -1;

	_ebx = 5;

	printf("%d %d \n", xs, uy);

	int y[4] = { 10, 20, 30, 40 };
	int *q;
	int a[2][5];
	int i = 1;
	int j = 2;
	int sum = 0;
	char  s[10];
	for (i=0;i<3;i++)
		for (j=0;j<5;j++)
	       array[i][j] = i*j;

	for (i = 0;i < 3;i++)
		for (j = 0;j < 5;j++)
			sum += array[i][j];
	array[1][2] += 30;
	i = 1;
	i = 2;
	printf("%d\n",sum);

	xxx[1] = 100;
	y[1] = 100;
	scanf_s("%s", s, 9);
	*(y + 2) = 90;
	a[i][j] = 10;
	for (i = 0; i < 2;i++)
	  for (j = 0; j < 5; j++)
		 a[i][j] = 0;

	y[i] = 100;

	q = y;
	q = q + 1;
	*q = 50;

	p = x;
	p = &(x[0]);
	p = p + 1;
	*p = 0x32;
	return 0;
}
