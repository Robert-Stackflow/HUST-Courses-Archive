#include<stdio.h>
int main(void)
{
	char c;
	//��������ַ�ת��Ϊ��д��ĸ 
	putchar(((c=getchar())>='a'&&c<='z')?c-'a'+'A':c);
	return 0;
 } 
