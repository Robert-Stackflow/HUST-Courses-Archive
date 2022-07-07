#include<stdio.h>
int gsq(int n)
{
	int i,x,a,t;
	x=2;
	for(;x<=n/2;x++)
	{
	i=x-1;
	for(;x%i!=0;) 
		i--;
	if(i==1)
	{
	t=n-x;
	a=t-1;
	if(a!=0)
	{
	for(;t%a!=0;) 
		a--;
	if(a==1) 
		printf("%d=%d+%d\n",n,x,t);
	}
	}
	}
}

int main(void)
{
	int n;
	scanf("%d",&n);
	gsq(n);
	return 0;
}

