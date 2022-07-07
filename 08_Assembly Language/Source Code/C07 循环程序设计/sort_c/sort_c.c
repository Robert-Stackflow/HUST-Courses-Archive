#include <stdio.h>
#define N 6
int main(int argc, char* argv[])
{
	int buf[N] = { -10, 20, 30, -100, 25, 60 };
	int  i;
	int  j;
	int  x = 20;
	int  y = 30;

	printf("x=%d y=%d \n", x, y);
	for (i = 0; i < N - 1; i++) {
	   for (j = i + 1; j < N;j++)
	      if (buf[i] > buf[j]) {
		     x = buf[i];
		     buf[i] = buf[j];
		     buf[j] = x;
	     }
	}
	for (i = 0; i < N;i++)
	   printf("%d ", buf[i]);
	return 0;
}