#include<stdio.h>
int main(void)
{
	unsigned short x,m,n;
	scanf("%hx%hu%hu",&x,&m,&n);
	if(!((m>=0&&m<=15)&&(n>=1&&n<=(16-m))))
		printf("m��n�����ݷ�Χ����\n"); 
	x=x>>m;
	x=x<<(16-n);
	printf("%hx",x);
	return 0;
} 
