#include "stdio.h"
char *(*(*p)(void))(char *,char *);/*f1��һ��ָ�뺯�������ص�ָ��ָ��������*/
char *(*f1(void))(char *,char *);/*�ַ�ָ���βΣ��ҷ���ֵΪ�ַ�ָ��ֵ�ĺ���*/
char *strcpy(char *,char *);/*�������ַ�ָ���βΣ��ҷ���ֵΪ�ַ�ָ��ֵ�ĺ���*/
int main(void)
{
	char a[80],b[]="aaa,bbb,ccc",*str;
	p=f1;/*pָ��f1*/
	str=(*p)()(a,b);/*�ȼ���(*p)()����f1����������strcpy��Ȼ�����strcpy(a,b)*/
	printf("%s\n",str);
	return 0;
}
char *(*f1(void))(char *,char *)
{/*f1(void)��ʾf1���޲κ��������ಿ�ֶ����������ķ���ֵ������*/
	return strcpy;/*f1����ָ���������ַ�ָ���βΣ��ҷ���ֵΪ�ַ�ָ��ֵ�ĺ���*/
}
char *strcpy(char *t,char *s)
{
	char *p=t;
	while((*t++=*s++)!='\0') ;
	return p;
}
