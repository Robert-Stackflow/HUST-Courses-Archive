#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
���ȫ����
���磬���������{a,b,c},��ô���������Ԫ�ص�����������{(a,b,c),(a,c,b),(b,a,c),(b,c,a),(c,a,b),(c,b,a)}����Ȼ������n��Ԫ�ع���n!�ֲ�ͬ������.
��������������ļ��㷨�������������У�������(a,b,c)�����������������������ɣ�

��1����a��ͷ�������(b,c)������
  
��2����b��ͷ�������(a,c)������
	
��3����c��ͷ�������(a,b)������

����Ȼ��һ�ֵݹ��˼·���������ǵõ������µ�ʵ�֣�
*/

void swap(char &a, char &b)
{
	char temp = a;
	a = b;
	b = temp;
}

//k��ʾ��ǰѡȡ���ڼ�����,m��ʾ���ж�����.  
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
	printf("ȫ���н��Ϊ��\n");
	Permutation(a, 0, strlen(a) - 1);
	system("pause");
	return 0;
}

//http://blog.csdn.net/morewindows/article/details/7370155