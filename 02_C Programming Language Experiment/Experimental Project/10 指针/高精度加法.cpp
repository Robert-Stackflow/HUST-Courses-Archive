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
	char a2[M] = { 0 }, b2[M] = { 0 };	//��ŵߵ�˳�������ִ�
	int c[1 + M] = { 0 };		

	gets(a);
	gets(b);

	len_a = strlen(a);
	len_b = strlen(b);

	int la = len_a - 1;
	int lb = len_b - 1;
	// ��β����˳�� �洢��a2[] b2[] ��  �������
	for (i = 0; i < len_a; i++)  
	{
		a2[la] = a[i]-48;		// ��ASCII ��ֵ ��ȥ48��48-57��  ��ʣ���� Ϊ 0-9
		la -= 1;
	}
	
	for (i = 0; i < len_b; i++)
	{
		b2[lb] = b[i]-48;
		lb -= 1;
	}
	int k=0;	// k �����λ����
	int j = 0;		// ����c[] �ĳ��� 
	int m = max(len_a, len_b);	// �����������һ���ĳ���  �Դ������� �������ֵ����
	int n = min(len_a, len_b);	// ������������̵�һ���ĳ��� �Դ˽��мӷ��ļ�ʱת��
	
	for(i=0;i<n;i++)		// �����������
	{
		c[j] = (a2[i] + b2[i]) + k;
		k = c[j]/10;
		c[j]=c[j]%10;
		j++;

		if (i == n - 1 && k>0)	// ���һ����λ
		{
			c[j] = k;
		}	
	}
	// ���������֮��  ʣ�µ�����ֱ�Ӹ�ֵ��c[]
	for (i = n; i<m; i++)
	{	
		if (len_a>len_b)	// ��ʣ��ĳ����� ���
		{	
			if (k > 0)
			{
				c[j] = a2[i] + k;	// �������֮���н�λ  �����9�Ļ� ����ط�û�н�λ ������ 
				if(c[j]==10)		// �����ж��������ok �� 
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
				c[j] = a2[i];		// �������֮���޽�λ
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
	for (i = j-1; i>=0; i--)	// �����������֮��ĺ͵��������  i=j-1 �Ӻ���ǰ���
	{
		printf("%d", c[i]);
	}
	return 0;
}

