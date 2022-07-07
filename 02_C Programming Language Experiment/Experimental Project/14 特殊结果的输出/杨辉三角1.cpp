//解法一
#include <stdio.h>
int main(){ 
	int i,j,n=0,a[17][17]={0};
	while(n<1 || n>16)
		{ printf("请输入杨辉三角形的行数:");
		scanf("%d",&n);
	}
	for(i=0;i<n;i++)
	a[i][0]=1; /*第一列全置为一*/
	for(i=1;i<n;i++)
	for(j=1;j<=i;j++)
	a[i][j]=a[i-1][j-1]+a[i-1][j];/*每个数是上面两数之和*/
	for(i=0;i<n;i++) /*输出杨辉三角*/
	{ for(j=0;j<=i;j++)
	printf("%5d",a[i][j]);
	printf("\n");
	}
}
//解法一是一般最容易想到的解法，各部分功能独立，程序浅显易懂。


