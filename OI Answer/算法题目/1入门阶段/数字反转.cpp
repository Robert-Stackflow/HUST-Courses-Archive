#include<stdio.h>
#include<stdlib.h>
int abs(int x)
{
	if(x>=0)return x;
	else return -x;
}
int main(void)
{
    int sign=1,n,m=0;
    scanf("%d",&n);
    if(n<0) sign=-1;
    n=abs(n);
    while(n>0)
	{
	m=m*10+n%10;
	n/=10;
	}
	m*=sign;
	printf("%d",m);
	return 0;
}
