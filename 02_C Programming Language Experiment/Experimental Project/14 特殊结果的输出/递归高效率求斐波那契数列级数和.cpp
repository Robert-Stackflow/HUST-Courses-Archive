#include<stdio.h>
long long fabonacci(long long a,long long b,int n)
{
	if(n>2)
	{
		return fabonacci(a+b,a,n-1);
	}
	return a;
}

int main (void)
{
	int k;
	long long a=1;
	long long b=1;
	long long sum=0;
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
		sum+=fabonacci(a,b,i);
	printf("%lld\n",sum);
	return 0;
}

