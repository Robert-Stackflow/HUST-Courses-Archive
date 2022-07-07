#include<stdio.h>
int main (void)
{
	int i,k;
	long sum=0,fabonacci(int n);
	printf("Input n:");
	scanf("%d",&k);
	for(i=1;i<=k;i++)
	{
		sum+=fabonacci(i);
		printf("i=%d\tthe sum is %ld\n",i,sum);
	}
	return 0;
}

long fabonacci(int n)
{
	long long a[1000]; 
	a[0]=0;
	if(n==1)
	{
		a[1]=1;
		return 1;
	}
	if(n==2)
	{
		a[2]=1;
		return 1;
	}
	else
	{
		a[n]=fabonacci(n-1)+fabonacci(n-2);
	}
	return a[n-2]+a[n-1];
}
