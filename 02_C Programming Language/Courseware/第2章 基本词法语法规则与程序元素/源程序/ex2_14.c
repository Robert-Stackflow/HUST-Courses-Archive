#include<stdio.h>
int main(void)
{
	char c;   /* ���ڴ�ŵ�ǰ������ַ� */
    int x;    /* ���ڴ��ת�������� */
    for(x=0,c=getchar();c>='0'&&c<='9';c=getchar())  /* �������ַ�����ѭ�� */
		x=10*x+c-'0';    /* c-'0'���������ַ�ת���ɶ�Ӧ��һλ���� */
	printf("x=%d\n",x);  /* ��� */
	return 0;
}
