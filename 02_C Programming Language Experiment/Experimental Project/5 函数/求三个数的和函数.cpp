#include<stdio.h>
int sum(int a,int b,int c)
{
	int sum;
	sum=a+b+c;
	printf("%d",sum);
 } 
 int main(void)
{
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	sum(a,b,c);
	return 0;
 } 
