#include<stdio.h>
int main()
{
  int i,j,m,base=1,n;
  int a[10][10]={1};
  scanf("%d",&n);
  for(m=0;m<n/2;m++)
   {
   	//当做完这四个动作后方阵变小，对应循环终止值要减小 
    for(i=m;i<=n-1-m;i++)
    //当向右输出时行不变列增加
    	a[m][i]=base++;
    for(j=m+1;j<n-1-m;j++)
    //向下输出时行增加列不变
        a[j][n-1-m]=base++;
    for(i=n-1-m;i>m;i--)
    //向左输出时行不变列减少
        a[n-1-m][i]=base++;
    for(j=n-1-m;j>m;j--)
    //当向上输出时行减少列增加
        a[j][m]=base++;
    if(n%2==1)
    //到最后一个值时若行数为奇数要单独输出 
        a[(n-1)/2][(n-1)/2]=base;
   }
   for(i=0;i<n;i++)
   {
    for(j=0;j<n;j++)
    {
    	printf("%2d",a[i][j]);
        if(j!=(n-1))
        printf(" ");
	} 
    printf("\n");
   }
   return 0;
} 
