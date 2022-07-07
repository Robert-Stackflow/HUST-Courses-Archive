#include<stdio.h>  
int main(void)
{
	int  i=1,sign=1;
	double m=0.0,n,k=1.0;
	double e;
	scanf("%lf",&e);
	while (((double)(1.0/i))>=e)
		{
			m=m+k;
        	sign*=-1;
        	i+=2;
        	k=1.0/i*sign;
		}
	m=m+k;
	n=(double)(m*4);
	printf("%lf",n);
}
