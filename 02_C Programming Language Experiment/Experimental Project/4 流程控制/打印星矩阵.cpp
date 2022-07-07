#include<stdio.h> 
#define line 25
#define raw  25 
int main(void)
{
	for(int i=0;i<raw;++i)
	{
		for(int j=0;j<line;++j)
			printf("*");
		printf("\n");
	}
}
