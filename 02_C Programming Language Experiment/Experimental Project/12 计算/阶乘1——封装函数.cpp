#include<stdio.h>
int fac(int n)
{
	int i;
	unsigned long fac=1;
	for(i=1;i<=n;++i)
		fac*=i;
	return fac; 
}
int main(void)
{
	int n,i;
	printf("������һ����������");
	scanf("%d",&n) ;
	printf("%d!�Ľ����%lu\n",n,fac(n)); 
	return 0; 
 } 
