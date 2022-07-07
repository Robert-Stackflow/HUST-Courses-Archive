#include<stdio.h>
void reverse(int m,int n,int *chess); 
int main()
{
	int n,m,i,j;
	scanf("%d %d",&n,&m);
	int chess[n][m];
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
			scanf("%d",*(chess+i)+j);
	}
	reverse(m,n,&chess[0][0]);
	return 0;
}
void reverse(int m,int n,int *chess)
{
	int mid[n][m];
	int *p=chess;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			*(*(mid+i)+j)=*(*(p+j)+m-i-1);
			printf("%d",*(*(p+j)+m-i-1));
			if(j<(n-1))  printf(" ");
		}
		printf("\n");
	}
}

