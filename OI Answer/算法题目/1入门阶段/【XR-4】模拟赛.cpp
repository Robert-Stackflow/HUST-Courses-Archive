#include<stdio.h>
int n,m,k,day[1002][1002],count[1002];
int main(void)
{
    
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<n;i++)
    	for(int j=0;j<m;j++)
			scanf("%d",&day[i][j]);
	for(int i=0;i<m;i++)
	{
		int flag[1002]={0};
		for(int j=0;j<n;j++)
		{
			if(flag[day[j][i]-1]==0)
			{
			count[day[j][i]-1]++;
			flag[day[j][i]-1]=1;
			}
		}
	}
	for(int i=0;i<k;i++)printf("%d ",count[i]);
	return 0;
}
