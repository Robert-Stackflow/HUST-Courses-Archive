#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define ERROR 0
#define OK 1
int suanfa(int a[], int n,int arrsize)
{
	if(n>arrsize) return 0;
	a[0]=2;
	for(int i=2;i<=n;i++)
	{
		a[i-1]=a[i-2]*2*i;
		if(a[i-1]<0) return 0;
	}
	return 1;
}
int main(void)
{
	int a[20];
	int n;
	int arrsize;
	scanf("%d,%d",&n,&arrsize);
	if(!suanfa(a,n,arrsize))
	{
	printf("ERROR");
	return 0;
	}
	for(int i=0;i<n;i++)
		printf("%d ",a[i]);
}
