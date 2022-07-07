#include<stdio.h> 
void judge(int n)
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
	{
		printf("%d=%d+%d\n",n,x,t);
		return; 
	} 
	}
	}
	}
} 
int main(void)
{
	int n;
	while(scanf("%d",&n)!=EOF)
			judge(n);
	return 0;
}
