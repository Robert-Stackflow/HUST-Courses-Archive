#include<stdio.h>
#include<math.h>
typedef struct{
	int n,m;
	int a[10][10];
}list;
list num[21];
int t,check[10][10],ans,res;
//check����������¼�õ㸽���м�����
int dirx[]={0,1,1, 1, 0,-1,-1,-1};
int diry[]={1,1,0,-1,-1,-1, 0, 1};
void dfs(int x,int y,int i);
int main(void)
{
	scanf("%d",&t);//�������ݵ�����
	for(int i=0;i<t;i++)
	{
		scanf("%d%d",&num[i].n,&num[i].m);
		//���뵱ǰ�����ݵ�����������
		for(int j=1;j<=num[i].n;j++)
			for(int k=1;k<=num[i].m;k++)
				scanf("%d",&num[i].a[j][k]);
				//��������
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
	if(y==num[i].m+1) {dfs(x+1,1,i);return;}//�����������β��������һ���ٴ�����
	if(x==num[i].n+1)	{ans=((ans>res)?ans:res);return;}
	//�����������β��Ƚϵ�ǰ�õ��Ľ�����ѵõ�����һ�ֽ����ȡ���ֵ
	dfs(x,y+1,i);//���������������������ͬ������������Ҳ����ȡ����
	if(check[x][y]==0)
	{//����õ�δ����ǣ�����Χû��ȡ����������ô�ͼ�����һ���ֵ
		res+=num[i].a[x][y];
		for(int p=0;p<8;p++)//���õ���Χ��ֵ���б��
			check[x+dirx[p]][y+diry[p]]++;
		dfs(x,y+1,i);// ���·�����
		for(int p=0;p<8;p++)//����
			check[x+dirx[p]][y+diry[p]]--;
		res-=num[i].a[x][y];
	}
}

