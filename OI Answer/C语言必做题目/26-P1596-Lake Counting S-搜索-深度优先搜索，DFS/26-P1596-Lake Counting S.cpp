#include<stdio.h>
#include<string.h>
int n,m,ans=0,check[105][105];
char area[105][105];//��¼��ͼ
int dirx[]={0,1,1, 1, 0,-1,-1,-1};
int diry[]={1,1,0,-1,-1,-1, 0, 1};
//�����㷨�İ˸�����
void sign(void);
void dfs(int x,int y);
int main(void)
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%s",&area[i]);
	sign();//����ͼת��Ϊ���ڴ������������
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			if(check[i][j]==1)//�����ˮ��������1����������
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
			if(area[i][j]=='W') check[i][j]=1;//��ˮ������Ϊ1
			else check[i][j]=0;
		}
	}
}
void dfs(int x,int y)
{
	check[x][y]=0;//����ʱ�Ȱѵ�ǰˮ�ݵ㸳ֵΪ0��ʾ���߹�
	for(int i=0;i<8;i++)
		if(check[x+dirx[i]][y+diry[i]]==1)
		//ѭ�������˸����������ˮ����Ը�ˮ�ݼ�����ǰ����
			dfs(x+dirx[i],y+diry[i]);
	//�ݹ�DFS����
}
