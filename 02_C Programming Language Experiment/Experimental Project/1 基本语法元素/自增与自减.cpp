#include<stdio.h> 
int main(void)
{
	int x=10,y,z,Y,Z;
	y=++x;
	z=--x;
	Y=x++;
	Z=x--;
	printf("y=%d,z=%d,Y=%d,Z=%d",y,z,Y,Z);
	return 0; 
}
