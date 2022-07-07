#include <stdio.h>
void  f()
{
	int  x;
	x = 20;
}
int main()
{
	double f1 = 3.2;
	double f2 = 3.4;
	double f3;
	int  x = 10;
	int y = 20;
	int  u = 30;
	int  v = 40;
	int  w = 50;
	f();
//	__int64 z = x + y;
	int z;
	z = x + y;
	f3 = f2 + f1;
	printf("hello \n");

	printf("%ld %d %d %d %d \n", x, y, z, u, v);

	printf("%f %d %d %d  %f\n", f1,x,y,z,f2);
	return 0;
}