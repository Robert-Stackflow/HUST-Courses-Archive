#include<stdio.h>
struct nn{
	int m;
	double n;
	char score[20];
}; 

int main(void)
{
	struct nn result;
	printf("%d",sizeof(result));
}
