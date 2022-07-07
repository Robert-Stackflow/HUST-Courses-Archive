#include<stdio.h>
int main(void)
{
	int x,factorial=1;
	printf("请输入一个正整数：");
	scanf ("%d",&x); 
	while (x!=1){ 
		factorial*=x;
		x=x-1;
	} 
	printf("您所求的数的阶乘是%d",factorial);
	return 0;
 } 
