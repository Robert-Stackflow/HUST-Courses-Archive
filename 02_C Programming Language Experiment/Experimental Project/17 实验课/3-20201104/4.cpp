#include<stdio.h> 
int main(void) 
{
	char a,b;
	printf("������һ�����ģ�����Ctrl+Z����:\n") ;
	while((b=getchar())!=EOF)
	{
		if(!(a==32&&b==32))//���ǰ�������ַ���Ϊ�ո���ֻ���һ�� 
		putchar(b);
		a=b;//����һ���ַ�����ǰһ���ַ� 
	}
	return 0;
}
