#include<stdio.h>
int main(void)
{
/*求三个数中的最大值*/
	float a,b,c,max;
	printf("请输入三个数:\n");
	scanf("%f%f%f",&a,&b,&c) ;
	if(a>=b&&a>=c)	max=a;
	if(b>=a&&b>=c)	max=b;
	if(c>=b&&c>=a)	max=c;
	printf("您输入的三个数中最大的数是max=%.2f",max);
	return 0;
}
