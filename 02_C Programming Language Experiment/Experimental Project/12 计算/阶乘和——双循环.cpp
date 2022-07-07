#include<stdio.h>
int main(void)
{
	long long factorial=1,sum=0; 
	for(int x=1;x<=20;x++)
	{
		factorial*=x;
		sum+=factorial;
	} 
	printf("您所求的数的前二十个数的阶乘的和是%lld",sum);
	return 0;
 } 
