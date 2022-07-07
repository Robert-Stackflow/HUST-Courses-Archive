#include<stdio.h>
#include<string.h>
int main(void)
{
	int n,count=0,num[100],check[1000]={0};
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
	scanf("%d",&num[i]);
	check[num[i]]=1;
	}
	for(int i=0;i<1000;i++)	if(check[i]) count++;
	printf("%d\n",count);
	for(int i=0;i<1000;i++)	if(check[i]) printf("%d ",i);
}
