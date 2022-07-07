#include <stdio.h>
int main(int argc, char* argv[])
{
	int x = 0x70000000;
	int y = 0x20000000;
	int z;
	z = x + y;
	printf("signed z   : %d + %d = %d\n", x, y, z);
	printf("unsigned z : %u + %u = %u\n", x, y, z);
	printf("           : %xH + %xH = %xH\n", x, y, z);
	return 0;
}