#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
输出全排列
例如，如果集合是{a,b,c},那么这个集合中元素的所有排列是{(a,b,c),(a,c,b),(b,a,c),(b,c,a),(c,a,b),(c,b,a)}，显然，给定n个元素共有n!种不同的排列.
可以用下面给出的简单算法产生其所有排列，即集合(a,b,c)的所有排列有下面的排列组成：

（1）以a开头后面跟着(b,c)的排列
  
（2）以b开头后面跟着(a,c)的排列
	
（3）以c开头后面跟着(a,b)的排列

这显然是一种递归的思路，于是我们得到了以下的实现：
*/

void swap(char &a, char &b)
{
	char temp = a;
	a = b;
	b = temp;
}

//k表示当前选取到第几个数,m表示共有多少数.  
void Permutation(char* a,int k,int m)
{
	int i;
	if(k == m)
	{
		for(i=0;i<=m;i++)
		{
			printf("%c", a[i]);
		}
		printf("\n");
	}
	else
	{
		for(i = k; i <= m; i++)
		{
			swap(a[i], a[k]);
			Permutation(a, k+1, m);
			swap(a[i], a[k]);
		}
	}
}
int main(void)
{
	char a[] = "abc";
	printf("全排列结果为：\n");
	Permutation(a, 0, strlen(a) - 1);
	system("pause");
	return 0;
}

//http://blog.csdn.net/morewindows/article/details/7370155