#include<stdio.h>
#include<string.h>
int n,m,ans=0,check[105][105];
char area[105][105];//记录地图
int dirx[]={0,1,1, 1, 0,-1,-1,-1};
int diry[]={1,1,0,-1,-1,-1, 0, 1};
//深搜算法的八个方向
void sign(void);
void dfs(int x,int y);
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%s",&area[i]);
	sign();//将地图转化为易于处理的整形数组
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(check[i][j]==1)//如果是水洼则结果加1并进行搜索
			{
				ans++;
				dfs(i,j);
			}
		}
	}
	printf("%d",ans);
}
void sign()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(area[i][j]=='W') check[i][j]=1;//是水洼则标记为1
			else check[i][j]=0;
		}
	}
}
void dfs(int x,int y)
{
	check[x][y]=0;//深搜时先把当前水洼点赋值为0表示已走过
	for(int i=0;i<8;i++)
		if(check[x+dirx[i]][y+diry[i]]==1)
		//循环遍历八个反向，如果是水洼则对该水洼继续向前搜索
			dfs(x+dirx[i],y+diry[i]);
	//递归DFS搜索
}
