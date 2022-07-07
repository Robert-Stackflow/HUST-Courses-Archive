#include<stdio.h>
#define max(m,n) (((m)>(n))?(m):(n))
int n,m,dp[105][10005],menu[105];
//dp数组存储的是选择了p道菜且金钱总数为q的方案数
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++) scanf("%d",&menu[i]);
	for (int p=1;p<=n;++p)
	{
        for (int q=1;q<=m;++q)
		{  
            if(q>menu[p-1])	dp[p][q]=dp[p-1][q]+dp[p-1][q-menu[p-1]];
            //如果当前背包容量大于价格那么就有选和不选两种选择
            //办法总数就等于吃这道菜的办法数与不吃这道菜的办法数之和
            else if(q==menu[p-1])	dp[p][q]=dp[p-1][q]+1;
			//如果背包容量恰好等于价格，那么就只有一种选择
			//此时这种情况本该包括在上种情况中但是dp[p][0]=0，因此要另归为1
            else	dp[p][q]=dp[p-1][q];
			//否则只能不选，办法总数就只能承袭吃前i-1道菜的办法总数
        }
	}
	printf("%d",dp[n][m]);
}
//算法改进之降维打击
#include<stdio.h>
int n,m,a[N],f[10010];
int main()
{

	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	f[0]=1;
	for(int i=1;i<=n;i++)
	    for(int j=m;j>=a[i];j--)
	    	f[j]=f[j]+f[j-a[i]];
	printf("%d",f[m]);
	return 0;
}

