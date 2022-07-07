#include<stdio.h>
#include<stdlib.h>
int n,m,count;
int dirx[]={0,1,1, 1, 0,-1,-1,-1};
int diry[]={1,1,0,-1,-1,-1, 0, 1};
int judge(int x,int y);
int main(void)
{
	scanf("%d%d",&n,&m);
	char map[n][m];
	for(int i=0;i<n;i++) scanf("%s",map[i]);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			count=0;
			if(map[i][j]=='*') continue;
			else 
			{
				for(int k=0;k<8;k++)
				if(judge(i+dirx[k],j+diry[k])==0) continue;
				else if(map[i+dirx[k]][j+diry[k]]=='*') count++;
			}
			map[i][j]=count+'0';
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			printf("%c",map[i][j]);
		printf("\n");
	}
		
}
int judge(int x,int y)
{
	if(x>=0&&x<n&&y>=0&&y<m) return 1;
	else return 0;
}
