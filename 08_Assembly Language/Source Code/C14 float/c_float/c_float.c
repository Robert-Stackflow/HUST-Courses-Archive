#include <stdio.h>
int main(int argc, char* argv[])
{
	float fx = 1.25;
	int   iy,  iz;
	iy = *(int *)&fx;
	iz = (int) fx;
	printf("%f %d %d\n", fx, iy,iz);
	return 0;
}

