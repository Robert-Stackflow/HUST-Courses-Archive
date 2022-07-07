#include<stdio.h>
int main(void)
{
	int a;
	printf("请输入一个整数：");
	scanf("%d",&a); 
	if(!(a%2)) 
		printf("%d is an even\n",a);
	else
		printf("%d is not an even\n",a);
	return 0;
}

