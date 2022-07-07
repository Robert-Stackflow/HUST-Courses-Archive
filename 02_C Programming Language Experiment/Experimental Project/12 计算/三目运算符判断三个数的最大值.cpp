#include<stdio.h> 
int main(void)
{
	int a,b,c,max;
	printf("请输入三个整数:");
	scanf("%d%d%d",&a,&b,&c);
	max=(a>b?(a>c?a:c):(b>c?b:c));
	printf("%d",max);
	return 0;
}
