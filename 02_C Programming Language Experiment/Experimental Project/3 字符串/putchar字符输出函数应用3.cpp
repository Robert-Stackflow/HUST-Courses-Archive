#include<stdio.h>
int main(void)
{
	int i;
	putchar(i=' ');
	putchar(i=32);
	putchar(i=10); //���з���� 
	putchar(i?'Y':'N');
	//Ҳ����������ʽ��ֵ 
	putchar('\a');//����������һ�� 
	return 0; 
}
