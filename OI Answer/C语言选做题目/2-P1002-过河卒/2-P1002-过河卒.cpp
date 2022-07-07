#include<stdio.h>
long long dp[30][30];
int x[9]={0,1,1,2,2,-1,-1,-2,-2};
int y[9]={0,2,-2,1,-1,2,-2,1,-1};
int chess[30][30];
int n,m,horsex,horsey;
int main(void)
{
	scanf("%d%d%d%d",&n,&m,&horsex,&horsey);
	for(int i=0;i<9;i++) chess[horsex+x[i]][horsey+y[i]]=1;
	dp[0][0]=1;
	for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
        {
        if(chess[i][j]||(i==0&&j==0))continue;
        if(i==0) dp[i][j]=dp[i][j-1];
        else if(j==0) dp[i][j]=dp[i-1][j];
        else dp[i][j]=dp[i][j-1]+dp[i-1][j];
        }
    printf("%lld\n",dp[n][m]);
    return 0;
}
