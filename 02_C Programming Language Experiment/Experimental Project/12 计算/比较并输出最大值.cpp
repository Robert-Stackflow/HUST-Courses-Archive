#include<stdio.h>
int main(void)
{
/*���������е����ֵ*/
	float a,b,c,max;
	printf("������������:\n");
	scanf("%f%f%f",&a,&b,&c) ;
	if(a>=b&&a>=c)	max=a;
	if(b>=a&&b>=c)	max=b;
	if(c>=b&&c>=a)	max=c;
	printf("�����������������������max=%.2f",max);
	return 0;
}
