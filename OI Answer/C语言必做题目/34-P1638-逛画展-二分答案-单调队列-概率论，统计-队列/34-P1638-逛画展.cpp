#include<stdio.h>
int n,m,sum,check[2050];
int main(void)
{
	scanf("%d%d",&n,&m);
	int pic[n+1];
	int right=1,left=1,ansl=1,ans=n,ansr=n;
	for(int i=1;i<=n;i++)	scanf("%d",&pic[i]);
	while(1)
	{
		while(right<=n&&sum<m)
			if(check[pic[right++]]++==0) sum++;
		if(sum<m)break;
		if(ans>(right-left))
		{
			ans=right-left;
			ansr=right-1;
			ansl=left;
		}
		if(--check[pic[left++]]==0) sum--;
	}
	printf("%d %d",ansl,ansr);
	return 0;
}
