#include<stdio.h> 
//求阶乘的函数1 
int factorial(int n){
	if (n==0||n==1)
		return 1;
	else
		return n*factorial(n-1);
}
//求阶乘的函数2 
int fac(int n)
{
	int i;
	unsigned long fac=1;
	for(i=1;i<=n;++i)
		fac*=i;
	return fac; 
}
//求三个数的最大值
int max(int a,int b,int c,int d)
{
	int max;
	max=(a>b?a:(b>c?b:(c>d?c:d)));
	return max;
} 
//判断素数
int isprime(int n)
{
	int flag=1;
	for(int i=2;i<=sqrt(n);i++)
	{
			if(n%i==0)
			{
				flag=0;
				break;
			}
	}
	return flag;			
}  
