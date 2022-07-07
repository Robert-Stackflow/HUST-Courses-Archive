#include<stdio.h> 
#include<math.h> 
#include<string.h>
/*样例输入
4 4 3 1 4
3 1 1 1 1
4 3 4 1 2
4 4 2 2 2 */ 
int main(void)
{
	int line,raw,count=1,flag=0;
	scanf("%d%d",&line,&raw); 
	int chess[100][100];
	int check[100][100]={0};
	//定义一个检查数组check，初始化为0，以实现当出现可消除的数字时将对应check数组的值置为1，从而得以消除 
	int j=0,k=0;
	//将棋盘存入数组中 
	for (int i=0;i<line;i++)
	{
		for(int j=0;j<raw;j++)
			scanf("%d",&chess[i][j]);	
	}
	//行遍历，当出现三个以上连续相同的数字时用循环将check数组对应的值置为1 
	for (int i=0;i<line;i++)
	{
		count=1;
		flag=chess[i][0];
		for(j=1;j<=raw;j++)
		{
			if(flag==chess[i][j])
				count++;	
			else
			{	
				if(count>=3) 
				{	
					while(count)
			  			{
							check[i][j-count]=1;
							count--;
						}
				}
				count=1;
				flag=chess[i][j];  
			}
		}
	}
	//列遍历，当出现三个以上连续相同的数字时用循环将check数组对应的值置为1 
	for (int i=0;i<raw;i++)
	{
		flag=chess[0][i];
		count=1;
		for(j=1;j<=line;j++)
		{
			if(flag==chess[j][i])
				count++;
			else
			{
				if(count>=3)
				{	
					while(count)
						{
							check[j-count][i]=1;
							count--;
						}
				}
				count=1;
				flag=chess[j][i];
			}
		}
	}
	printf("\n\n"); 
	//格式化输出——当check的值为1时输出0，否则输出棋盘中数字 
	for (int i=0;i<line;i++)
	{
		for(int j=0;j<raw;j++)
			{
			if(check[i][j]==1)
			{
				printf("0");
				if(j<raw-1)
				printf(" ");
			}
			else
			{
				printf("%d",chess[i][j]);
				if(j<raw-1)
				printf(" ");
			}
						
	} 
	printf("\n");
}
return 0;
}
