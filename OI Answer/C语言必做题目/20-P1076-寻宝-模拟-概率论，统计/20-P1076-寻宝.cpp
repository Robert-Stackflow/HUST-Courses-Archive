#include<stdio.h>
/*
3 3
1 2
0 3
1 4
0 1
1 5
1 2
0 2
1 8
1 7
1
*/
typedef struct area{
	int sign[101];
	int num[101];
}list;
int main(void)
{
	int n,m,k,check=0,ans=0,flag=0,mid=0;
	long long result=0;
	scanf("%d%d",&n,&m);
	list room[n+1];
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			scanf("%d%d",&room[i].sign[j],&room[i].num[j]);
	scanf("%d",&check);
	k=check;
	result=room[0].num[k];
	for(int i=0;i<n;i++)
	{	
		check=k;
		for(int j=0;j<m;j++) {if(room[i].sign[j]) ++flag;}
		mid=(room[i].num[check])%flag+flag;
		//����ò�¥�ܹ��ж��ٸ���������¥�ݵģ��Ӷ�����ѭ���� 
		for(int j=k;ans<mid;j++)
		{
			if(room[i].sign[j]) {k=j;++ans;}
			if(j>=m-1) j=-1;
		}
		//����ָʾ��Ѱ����¥�ݵķ��䣬���ҹ�һȦ������Ѱ�ң��������� 
		if(i<n-1) result+=room[i+1].num[k];
		ans=flag=0;
	}
	printf("%d",result%20123);
}

