#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int main()
{
	//�������������ô�������һ��ͬʱ�����ַ�,���֣���㣬�ո���ַ����������������
	char s[100],temp[100]/*tempΪ������*/;
	int i,j,k;
	gets(s);
	for(i = 0;s[i] != '\0';i++)
	{
		if(isdigit(s[i]))//��������֣�����뻺���� 
			temp[j++] = s[i];
		else 
		{
			if(j > 0)
			{//������������һ������д������֣���������ҽ����������� 
				temp[j] = '\0';
				puts(temp);
				j = 0;
			}else	continue;//������������һ������в��������飬��������� 
		}
	}
	
	if(j)//��ֹ��β��������	
	{
		temp[j] = '\0';
		puts(temp);
	}
}
