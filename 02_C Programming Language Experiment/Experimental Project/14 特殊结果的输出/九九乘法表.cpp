#include<stdio.h> 
int main(void)
{
	int m=1,n=1; 
	for(int i=0;i<9;++i)
	{
		for(int j=0;j<=i;++j)
		{
			for(;n<=m;++n)
			{
				printf("%d*%d=%d\t",n,m,m*n);
			}
		}
		m++;
		n=1;
		printf("\n");
	}
}
