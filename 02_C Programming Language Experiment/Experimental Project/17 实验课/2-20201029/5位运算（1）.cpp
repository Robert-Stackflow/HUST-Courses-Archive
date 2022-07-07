#include<stdio.h>
int main(void)
{
	unsigned short x,m,n,h;
	scanf("%hx%hu%hu",&x,&m,&n);
	if(!((m>=0&&m<=15)&&(n>=1&&n<=(16-m))))
		printf("m和n的数据范围错误！\n"); 
	h=x<<(16-(m+n+1))&(~0>>16-(m+n+1));
	printf("%hx",h);
	return 0;
} 
