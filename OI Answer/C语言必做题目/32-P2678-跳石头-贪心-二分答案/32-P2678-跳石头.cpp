#include<stdio.h>
#define N 50005
int len,n,m;
int main(void)
{
	scanf("%lld%d%d",&len,&n,&m);
	int map[N],dis[N];
	map[0]=0;
	map[n+1]=len;
	for(int i=1;i<=n;i++)
		scanf("%d",&map[i]);
	int left=0,right=len,mid,check=0;
	while(left<right-1)
	{
		check=0;
		mid=(left+right)/2;
		for(int i=1;i<=n+1;i++)
			dis[i]=map[i]-map[i-1];
		for(int i=1;i<=n+1;i++)
		{
			if(dis[i]<mid)
			{
				dis[i+1]+=dis[i];
				check++;
			}
		}
		if(check<=m) left=mid;
		else right=mid;
	}
	if(n==0) printf("%d",right);
	else	printf("%d",left);
}
