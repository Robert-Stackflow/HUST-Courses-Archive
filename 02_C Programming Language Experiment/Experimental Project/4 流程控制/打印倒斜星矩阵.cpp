#include<stdio.h> 
#define raw  25
int main(void)
{
	for(int i=0;i<raw;++i)
	{
		for(int j=i;j<raw;++j)
			printf("*");
		printf("\n");
	}
}
