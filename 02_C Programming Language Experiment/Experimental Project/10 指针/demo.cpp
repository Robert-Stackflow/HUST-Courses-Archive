#include<stdio.h>
int demo(int v1,int v2,int v3,int *p1,int *p2)
{
	int sum=v1+v2+v3;
	*p1=sum;
	int m=v1-v2-v3;
	*p2=m;
	int average=sum/3;
	return average;
 } 
int main()
{
	int res3=demo(a,b,c,&res1,&res2);
	printf("和=%i,差=%i,平均值=%i",res1,res2,res3);
}

