#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define M 101
#define max(x,y) (x>y ? x:y)
#define min(x,y) (x<y ? x:y)
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	int i;
	int len_a, len_b;
	char a[M], b[M];
	char a2[M] = { 0 }, b2[M] = { 0 };	//存放颠倒顺序后的数字串
	int c[1 + M] = { 0 };		

	gets(a);
	gets(b);

	len_a = strlen(a);
	len_b = strlen(b);

	int la = len_a - 1;
	int lb = len_b - 1;
	// 首尾调换顺序 存储在a2[] b2[] 中  方便相加
	for (i = 0; i < len_a; i++)  
	{
		a2[la] = a[i]-48;		// 将ASCII 码值 减去48（48-57）  所剩数字 为 0-9
		la -= 1;
	}
	
	for (i = 0; i < len_b; i++)
	{
		b2[lb] = b[i]-48;
		lb -= 1;
	}
	int k=0;	// k 保存进位数据
	int j = 0;		// 数组c[] 的长度 
	int m = max(len_a, len_b);	// 两个数组最长的一个的长度  以此来进行 所有数字的相加
	int n = min(len_a, len_b);	// 两个数字与最短的一个的长度 以此进行加法的及时转换
	
	for(i=0;i<n;i++)		// 两个数组相加
	{
		c[j] = (a2[i] + b2[i]) + k;
		k = c[j]/10;
		c[j]=c[j]%10;
		j++;

		if (i == n - 1 && k>0)	// 最后一个进位
		{
			c[j] = k;
		}	
	}
	// 将短数相加之后  剩下的数据直接赋值给c[]
	for (i = n; i<m; i++)
	{	
		if (len_a>len_b)	// 与剩余的长的数 相加
		{	
			if (k > 0)
			{
				c[j] = a2[i] + k;	// 两数相加之后还有进位  如果是9的话 这个地方没有进位 有问题 
				if(c[j]==10)		// 加上判定条件后就ok 了 
				{
					c[j]%=10;
					k=1;
				}
				else
				{
					k=0;
				}
			}
			else
				c[j] = a2[i];		// 两数相加之后无进位
			j++;
		}
		else
		{
			if (k > 0)	
			{	
				c[j] = b2[i] + k;
				if(c[j]==10)
				{
					c[j]%=10;
					k=1;
				}
				else
				{
					k=0;
				}
			}
			else
				c[j] = b2[i];	
			j++;
		}
	}
	if(len_a == len_b && k>0)
		printf("1");
	for (i = j-1; i>=0; i--)	// 两个数组相加之后的和的数据输出  i=j-1 从后往前输出
	{
		printf("%d", c[i]);
	}
	return 0;
}

