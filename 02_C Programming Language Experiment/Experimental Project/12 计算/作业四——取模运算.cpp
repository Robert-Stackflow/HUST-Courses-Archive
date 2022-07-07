#include<stdio.h> 
int main(void)
{
	int a;
	printf("请输入一个正整数：");
	scanf("%d",&a) ;
	if(!(a%3)&&(a%10==5))
		printf("1");
	else
		printf("0");
	return 0;
}
