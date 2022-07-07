#include<stdio.h>
void f(void)
{
	int i=1;
	for(;i<5;++i)
	{
		printf("1\n");
		return;//break?
	}
	printf("2\n");
} 
int main(void)
{
	f();
	return 0;
}
