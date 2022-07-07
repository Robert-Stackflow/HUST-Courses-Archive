#include<stdio.h>
double average(int a,int b,int c,int d)
{
	int sum;
	sum=a+b+c+d;
	double average;
	average=(double)(sum/4);
	printf("%.2lf",average);
 } 
 int main(void)
{
	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	average(a,b,c,d);
	return 0;
 } 
