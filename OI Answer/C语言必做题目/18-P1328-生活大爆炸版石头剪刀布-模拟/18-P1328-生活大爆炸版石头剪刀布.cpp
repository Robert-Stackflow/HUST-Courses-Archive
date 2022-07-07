#include<stdio.h>
int judge(int a,int b);
int main(void)
{
	int n,n1,n2,t1[201],t2[201],score1=0,score2=0;
	scanf("%d%d%d",&n,&n1,&n2);
	for(int i=0;i<n1;i++)	scanf("%d",&t1[i]);
	for(int i=0;i<n2;i++)	scanf("%d",&t2[i]);
	for(int i=n1;i<n;i++) t1[i]=t1[i-n1];
	for(int i=n2;i<n;i++) t2[i]=t2[i-n2];
	//复制扩展数组，避免循环进行比赛的复杂性 
	for(int i=0;i<n;i++)
	{
		if(judge(t1[i],t2[i])==2) ++score1;
		else if(judge(t1[i],t2[i])==0) ++score2;
	}
	printf("%d %d",score1,score2);
}
int judge(int a,int b)
{
	int flag=0;
	if(a==b) flag=1;
	else
	{
	if(a==0){if(b==2||b==3) flag=2;}
	if(a==1){if(b==0||b==3) flag=2;}
	if(a==2){if(b==1||b==4) flag=2;}
	if(a==3){if(b==2||b==4) flag=2;}
	if(a==4){if(b==0||b==1) flag=2;}
	}
	return flag;
}
