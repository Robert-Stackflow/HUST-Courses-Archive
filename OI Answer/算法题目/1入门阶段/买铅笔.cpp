#include<stdio.h>
#define min(x,y) ((x)<(y)?(x):(y))
int main(void)
{
    int n,p,q,ans=1e9;
    scanf("%d",&n);
    for(int i=0;i<3;i++)
	{
		scanf("%d%d",&p,&q);
		ans=min(ans,((n%p)?(n/p+1):(n/p))*q);
	}
	printf("%d",ans);
}
