#include<stdio.h>
double mulx(double x,int n);
long fac(int n);

double sum(double x,int n)
{
	double sum;
	
}

double mulx(double x,int n)
{
	int i;
	double z=1.0;
	for(i=0;i<n;i++)
	{
		z=z*x;
	}
	return z;
}

long fac(int n)
{
	
}

int main()
{
	double x;
	int n;
	scanf("%lf%d",&x,&n);
	printf("The result is %lf",sum(x,n));
	return 0;
} 
