#include<stdio.h>
int main(void)
{
	int a;
	printf("������һ��������");
	scanf("%d",&a); 
	if(!(a%2)) 
		printf("%d is an even\n",a);
	else
		printf("%d is not an even\n",a);
	return 0;
}

