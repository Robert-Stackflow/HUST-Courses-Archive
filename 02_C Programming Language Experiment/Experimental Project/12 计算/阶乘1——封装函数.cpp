#include<stdio.h>
int fac(int n)
{
	int i;
	unsigned long fac=1;
	for(i=1;i<=n;++i)
		fac*=i;
	return fac; 
}
int main(void)
{
	int n,i;
	printf("请输入一个正整数：");
	scanf("%d",&n) ;
	printf("%d!的结果是%lu\n",n,fac(n)); 
	return 0; 
 } 
