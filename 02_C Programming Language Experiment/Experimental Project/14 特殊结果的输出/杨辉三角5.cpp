//解法五
#include <stdio.h>
int main()
{ 
	int i,j,n=0,a[17]={1},b[17];
	while(n<1||n>16)
	{ 
		printf("请输入杨辉三角形的行数:");
		scanf("%d",&n);
	}
	for(i=0;i<n;i++)
	{ 
		b[0]=a[0];
			for(j=1;j<=i;j++)
				b[j]=a[j-1]+a[j]; /*每个数是上面两数之和*/
					for(j=0;j<=i;j++)
	{ 				a[j]=b[j]; /*把算得的新行赋给a,用于打印和下一次计算*/
						printf("%5d",a[j]);
	}
		printf("\n");
	}
}

