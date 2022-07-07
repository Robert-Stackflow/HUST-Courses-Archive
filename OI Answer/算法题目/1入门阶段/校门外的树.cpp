#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    int l,m,left,right,ans=0,area[10005];
	scanf("%d%d",&l,&m);
	for(int k=0;k<=l;k++)	area[k]=1;
	for(int i=0;i<m;i++)
	{
	scanf("%d%d",&left,&right);
	for(int j=left;j<=right;j++)	area[j]=0;
	}
	for(int k=0;k<=l;k++)	if(area[k]) ans++;
 	printf("%d",ans);
	return 0;
}
