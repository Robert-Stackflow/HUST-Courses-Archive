
//解法三

#include <stdio.h>

main()

{ int i,j,n=0,a[17][17]={0,1};

while(n<1 || n>16)

{ printf("请输入杨辉三角形的行数:");

scanf("%d",&n);

}

for(i=1;i<=n;i++)

for(j=1;j<=i;j++)

a[i][j]=a[i-1][j-1]+a[i-1][j]; /*每个数是上面两数之和*/

for(i=1;i<=n;i++) /*输出杨辉三角*/

{ for(j=1;j<=i;j++) printf("%5d",a[i][j]);

printf("\n");

}

}

//解法三是在解法一、二的基础上，把第一列置为1的命令去掉了，注意初始化数组的变化。


