#include <stdio.h>
int* f()
{
	int t;
	t = 100;
	return &t;
}

int main(int argc, char* argv[])
{
	int  *p;
	p = f();
	printf("%d\n", *p);
	printf("%d\n", *p);
	return 0;
}