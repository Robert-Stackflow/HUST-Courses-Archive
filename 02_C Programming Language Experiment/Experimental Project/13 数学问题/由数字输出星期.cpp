#include<stdio.h> 
int main(void)
{
	int x;
	char s[80]="零一二三四五六七",c[]="星期";
	scanf("%d",&x);
	if ((x>=1)&&(x<=7))
		c[2]=s[x];
		printf("%s",c);
		return 0;
}
