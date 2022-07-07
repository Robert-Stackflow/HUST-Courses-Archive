#include<stdio.h>
#define scale 100000//可改变素数表输出范围 
int main()
{
	printf("请输入一个范围在[4,1000000]之间的值："); 
	long long i, j, a[scale],prime[scale];
	for (a[0]=a[1]=0,i=2;i<scale;i++)
		a[i]=1;
	for (i=2;i<scale;i++)
	{
		if(a[i]){
			for (j=i*2;j<scale;j+=i)
				a[j]=0;//筛掉素数的倍数 
		}
	}
	long long n=0;
	for(i=2;i<scale;++i)
	{
		if(a[i])
		{
			prime[n]=i;
			++n;//将表中的下标（素数）存入素数表中 
		}
	}
	long long m;
	scanf("%lld",&m);
	long long q=0;
	for (;prime[q+1]<m;q++)//查找素数表输出孪生素数 
	{
		if(prime[q+1]-prime[q]==2)
		printf("(%lld,%lld)\n",prime[q],prime[q+1]);
	}
	return 0;
}
