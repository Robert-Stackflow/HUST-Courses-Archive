#include <stdio.h>
int main()
{ 
	int i,j,a[100][100];
	for(i=0;i<10;++i)
		a[i][0]=1;
	for(i=0;i<10;++i)
	{
		for(j=1;j<10;++j)
		a[i][j]=(a[i][j-1])*(i-j+1)/j;
	}
	for (i=0;i<10;++i)
	{
		for(j=i;j<10;++j)
			printf("  ");
		for(j=0;j<10;++j)
		{
			if(a[i][j]!=0)
				printf("%4d",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}

