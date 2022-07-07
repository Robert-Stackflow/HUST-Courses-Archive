#include<stdio.h> 
#define raw  25
int main(void)
{
	for(int i=1;i<raw;i+=1)
	{
		for (int j=1,k=1;j<=(raw-i);++j,++k)
			printf(" ");
		for (int k=1;k<=i;++k)
			printf("* ");	
		printf("\n");
	}
}
