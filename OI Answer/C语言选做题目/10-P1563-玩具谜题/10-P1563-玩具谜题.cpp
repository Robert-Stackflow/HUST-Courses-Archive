#include<stdio.h>
int main(void)
{
	int n,m,position=1,cmd=1;
	scanf("%d%d",&n,&m);
	int head[n+1],flag[m+1][2];
	char name[n+1][11];
	for(int i=1;i<=n;i++)scanf("%d%s",&head[i],name[i]);
	for(int i=1;i<=m;i++)scanf("%d%d",&flag[i][0],&flag[i][1]);
	for(int i=1;i<=m;i++)
    {
        if((head[position]==0&&flag[i][0]==0)||(head[position]==1&&flag[i][0]==1)) cmd=-1;
        else cmd=1;
        position=position+cmd*flag[i][1];
        if(position<1) position+=n;
        else if(position>n) position-=n;
    }
    printf("%s",name[position]);
}
