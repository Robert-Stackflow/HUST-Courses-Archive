#include<stdio.h> 
int main(void)
{
	int a;
	printf("������һ����������");
	scanf("%d",&a) ;
	if(!(a%3)&&(a%10==5))
		printf("1");
	else
		printf("0");
	return 0;
}
