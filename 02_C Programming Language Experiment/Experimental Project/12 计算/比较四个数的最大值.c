#include<stdio.h>
int maximum(int a,int b,int c,int d)
{
	int max;
	max=(a>b?a:(b>c?b:(c>d?c:d)));
	return max;
}
int main(void)
{
	int a,b,c,d,Max;
	printf("�������ĸ�������")	;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	Max=maximum(a,b,c,d);
	printf("���ֵ��%d",Max);
	return 0;
}
