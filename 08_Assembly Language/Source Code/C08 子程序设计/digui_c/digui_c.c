#include <stdio.h>
int jiecheng(int x)
{
	int t;
	if (x ==1)
		return 1;
	t = jiecheng(x - 1);
	t = t*x;
	return t;
}

int main(int argc, char* argv[])
{
	int  a = 3;
	int  b;
	b = jiecheng(a);
	printf("%d\n",b);
	return 0;
}