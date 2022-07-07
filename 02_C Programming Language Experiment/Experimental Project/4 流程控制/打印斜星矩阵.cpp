#include<stdio.h> 
#define raw  25
int main(void)
{
	for(int i=1;i<raw;++i)
	{
		for(int j=0;j<i;++j)
			printf("*");
		printf("\n");
	}
}
