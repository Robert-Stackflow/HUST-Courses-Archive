#include<stdio.h>
#include<math.h>
typedef struct{
	int n,m;
	int a[10][10];
}list;
list num[21];
int t,check[10][10],ans,res;
//check数据用来记录该点附近有几个数
int dirx[]={0,1,1, 1, 0,-1,-1,-1};
int diry[]={1,1,0,-1,-1,-1, 0, 1};
void dfs(int x,int y,int i);
int main(void)
{
	scanf("%d",&t);//读入数据的组数
	for(int i=0;i<t;i++)
	{
		scanf("%d%d",&num[i].n,&num[i].m);
		//读入当前组数据的行数和列数
		for(int j=1;j<=num[i].n;j++)
			for(int k=1;k<=num[i].m;k++)
				scanf("%d",&num[i].a[j][k]);
				//读入数据
	}
	for(int i=0;i<t;i++)
	{
		ans=0;
		dfs(1,1,i);
		printf("%d\n",ans);
	}
}
void dfs(int x,int y,int i)
{
	if(y==num[i].m+1) {dfs(x+1,1,i);return;}//如果遍历到行尾则行数加一后再次搜索
	if(x==num[i].n+1)	{ans=((ans>res)?ans:res);return;}
	//如果遍历到列尾则比较当前得到的结果与已得到的上一轮结果，取最大值
	dfs(x,y+1,i);//若均不是以上两种情况则同行向右搜索，也即不取此数
	if(check[x][y]==0)
	{//如果该点未被标记，即周围没有取其他数，那么就加上这一点的值
		res+=num[i].a[x][y];
		for(int p=0;p<8;p++)//将该点周围的值进行标记
			check[x+dirx[p]][y+diry[p]]++;
		dfs(x,y+1,i);// 向下方搜索
		for(int p=0;p<8;p++)//回溯
			check[x+dirx[p]][y+diry[p]]--;
		res-=num[i].a[x][y];
	}
}

