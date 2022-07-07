#include<stdio.h>
int main(void)
{
	int n,ans=0;
	scanf("%d",&n);
	int map[10005]={0},left[10005]={0};
	for(int i=1;i<=n;i++) scanf("%d",&map[i]);
	for(int flag=1;flag>=0;flag--)
	{
	left[1]=flag;
	for(int i=2;i<n+2;i++)
    {
    	left[i]=map[i-1]-left[i-1]-left[i-2];
    	if (left[i]!=1&&left[i]!=0)
    	{
    		ans--;
    		break;
    	}
    	if (i==n+1&&left[i]!=0)
    	{
    		ans--;
    		break;
    	}
    }
	}
    printf("%d",ans+2);
}
