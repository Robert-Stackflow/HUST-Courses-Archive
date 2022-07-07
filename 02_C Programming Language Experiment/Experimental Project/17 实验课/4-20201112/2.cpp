#include<stdio.h> 
long long isperfect(long long x)
{
	int a[10000];
	int count=0;
	long long j=1;
	long long sum=0;
	for(int i=0;j<x;j++)
	{
		if(x%j==0)
		{
			a[i]=j;
			i++;
			count++;
		}
	}
	for(int k=0;k<count;k++)
				sum+=a[k];
	if(sum==x)
	{	
		printf("%lld=",x);
		for(int m=0;m<count;m++)
			{	
				printf("%lld",a[m]);
				if(m<count-1)
				{
					printf("+");
				} 
				else printf("\n");	
			}
	} 	
	else
	printf("%lld is not a perfect number"); 
}
int main(void)
{
	long long x;
	scanf("%lld",&x);
		isperfect(x);
	return 0;
}
