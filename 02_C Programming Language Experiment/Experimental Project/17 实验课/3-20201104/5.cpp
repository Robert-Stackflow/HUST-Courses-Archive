#include <stdio.h>
int main()
{ 
	int i,j,a[100][100];//定义一个二维数组，代表行和列 
	for(i=0;i<10;++i)
		a[i][0]=1;//通过遍历，将第一列的值赋为1 
	for(i=0;i<10;++i)
	{
		for(j=1;j<10;++j)
		a[i][j]=(a[i][j-1])*(i-j+1)/j;//应用公式将值存入二维数组中 
	}
	for (i=0;i<10;++i)
	{
		for(j=i;j<10;++j)
			printf("  ");//打印空格，形成三角格式 
		for(j=0;j<10;++j)
		{
			if(a[i][j]!=0) 
				printf("%4d",a[i][j]);//按一个数字占四个字符的域宽输出 
		}
		printf("\n");//确保换行输出 
	}
	return 0;
}

