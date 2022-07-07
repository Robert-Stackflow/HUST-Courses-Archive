#include <stdio.h>
int main(int argc, char* argv[])
{
	int x[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	int y[12] = { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 }; 
	int i;
	for (i = 0; i < 12; i++)
		x[i] = x[i] + y[i];
	return 0;
}
