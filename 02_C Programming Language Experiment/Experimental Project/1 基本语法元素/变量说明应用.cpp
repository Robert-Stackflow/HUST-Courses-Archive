#include<stdio.h>
int main()
{
	int x=4,y=3,z=2;
	char c='a';
	if(c=='A'+32)
		printf("��ʽ��1��ȷ\n");
	else
	    printf("��ʽ��1����ȷ\n");
	if(c+1!='b') 
		printf("��ʽ��2��ȷ\n");
	else
	    printf("��ʽ��2����ȷ\n");
	if(x-y<=10)
		printf("��ʽ��3��ȷ\n");
	else
	    printf("��ʽ��3����ȷ\n");
	if(z=x>y)
		printf("��ʽ��4��ȷ\n");
	else
	    printf("��ʽ��4����ȷ\n");
	if(x>y>z)
		printf("��ʽ��5��ȷ\n");
	else
	    printf("��ʽ��5����ȷ\n");
	return 0;
 } 
