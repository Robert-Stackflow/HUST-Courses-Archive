#include<stdio.h>
#define N 5050
#define M 1050
#define max(m,n) (((m)>(n))?(m):(n))
int m,n,step[N][M]={0},flag=1,ans=0;
int len(int *s);
int main(void)
{
	scanf("%d%d",&m,&n);
	if(n==0) {printf("0"); return 0;} 
	if(n==1) {printf("1"); return 0;} 
	step[0][1]=0;
	step[1][1]=1;
	step[2][1]=2;
	for(int i=3;i<=n-m;i++)
	{
		for(int j=1;j<=M;j++)
		{
			step[i][j]=step[i-1][j]+step[i-2][j]+ans;
			ans=step[i][j]/10;
			step[i][j]-=ans*10;
		}
	}
	for(int i=N;i>=1;i--)
	{
		if(flag&&step[n-m][i]==0)continue;
		flag=0;
		printf("%d",step[n-m][i]);
	}
}
int len(int *s)
{
	int i;
	for(i=0;s[i];i++);
	return i;
}
