#include <stdio.h>
int main()
{ 
	int i,j,n=0,a[17]={0,1},l,r;
	while(n<1||n>16)
    { 
	printf("请输入杨辉三角形的行数:");
	scanf("%d",&n);
	}
	for(i=1;i<=n;i++)
	{ 
		l=0;
	for(j=1;j<=i;j++)
	{ 
		r=a[j];
		a[j]=l+r; /*每个数是上面两数之和*/
		l=r;
		printf("%5d",a[j]); 
		printf(" ");
	}
		printf("\n");
	}
}
//解法六只使用了一个一维数组和两个临时变量。
