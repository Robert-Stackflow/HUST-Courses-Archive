#include<stdio.h>
int main(void)
{
	int x,factorial=1;
	printf("������һ����������");
	scanf ("%d",&x); 
	while (x!=1){ 
		factorial*=x;
		x=x-1;
	} 
	printf("����������Ľ׳���%d",factorial);
	return 0;
 } 
