#include "stdio.h"
#include "stdio.h"
char *strstr(char *s,char *t)/*sΪԴ��,tΪ�ִ�*/
{	char *ps=s,*pt,*pc;/*psָ��Դ��*/
	while(*ps!='\0'){/*ps����ָ��Դ����ÿһ���ַ�*/
		for(pt=t,pc=ps;*pt!='\0'&& *pt==*pc;pt++,pc++)/*pcָ��Դ��,ptָ���ִ�;*/ 
			;/*��Դ���ַ����ִ��ַ�ƥ����û���ִ�β,pt++,pc++������*/
		  if(*pt=='\0') return ps;/*���ִ�β��˵��ƥ��ɹ��������ִ�����λ��*/
		  ps++;/*psָ��Դ���е���һ���ַ�*/
	}
	return 0;
}
int main(void)
{	char s1[]="abcdefghijk",s2[]="fgh",*p;/*����Դ��,�ִ�,��ʱָ��p*/
	p=strstr(s1,s2);/*��"abcdefghijk"�в���"fgh",�ִ�����λ�ø���p*/
	printf("%p\t%s\n",&s1[0],s1);/*���Դ����ʼ��ַ��Դ��*/
	printf("%p\t%s\n",p,p);/*����ִ�����λ���Լ��Ӹ�λ�����Դ��*/
	return 0;
}

