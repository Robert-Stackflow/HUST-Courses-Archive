#include<stdio.h>
int swap(int a,int b)
{
	int t;
	t=a;
	a=b;
	b=t;
 } 
 int main()
 {
	int a=10;
	int b=20;
	swap(a,b);
	printf("%d\t%d",a,b);
 }
