#include<stdio.h>
#define N 4
#define max(m,n) (((m)>(n))?(m):(n))
int main(void)
{
	int work[5],sum=0,dp[100][1500]={0},ans=0;
	for(int i=0;i<N;i++)scanf("%d",&work[i]);
	int time[5][61];
	for(int i=0;i<N;i++)
	{
		sum=0;
		for(int j=0;j<work[i];j++)
		{
			scanf("%d",&time[i][j]);
			sum+=time[i][j];
		}//读入该科目每道题所用的时间并计算所有题用时和
		if(work[i]==1) ans+=time[i][0];//如果仅有一道题，答案易得
		else if(work[i]==2) ans+=max(time[i][0],time[i][1]);
		//如果仅有两道题，答案即为较大的时间值
		else
		{//否则进入背包算法，物品数是work[i]，物品的价值和用时（近似于体积）相同。
		for (int p=1;p<=work[i];++p)//work[i]指示该科目题目的数目
		{
        for (int q=1;q<=sum/2;++q)
		{ //背包容量也即总时间和的一半
            if(q>=time[i][p-1])//q表示当前的背包容量
            //如果q大于等于当前题目所需的时间那么物品数为p的背包问题归结于
            //放入p和不放入p两种情况，取最大值
            dp[p][q]=max(dp[p-1][q],dp[p-1][q-time[i][p-1]]+time[i][p-1]);
            else//如果q小于当前题目所需的时间，则p无法放入结果唯一
            dp[p][q]=dp[p-1][q];
        }
    	}
		ans+=max(sum-dp[work[i]][sum/2],dp[work[i]][sum/2]);
		//该科目总用时即为两半大脑用时的最大值
		}
//		printf("--%d--\n",ans);
	}
	printf("%d",ans);
}
