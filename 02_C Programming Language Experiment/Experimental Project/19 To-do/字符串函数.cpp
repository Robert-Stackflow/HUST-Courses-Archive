#include<stdio.h> 
#include<string.h>
//��ĳ�ַ����Ե�n���ַ�����ַ��������м��ַ����У�����ԭ�ַ�������n֮����ַ�ɾ�� 
void codel(char t[],char mid[],int n)
{
	int i=0,k=n;
	for(;t[k]!='\0';i++,k++)
		mid[i]=t[k];
	mid[i]='\0';
	t[n]='\0';
}
//���ַ���sƴ�ӵ��ַ���t�� 
void strcate(char t[],char s[])
{
	int i=0,j=0,k=-1;
	while(t[i++]);
	i--;
	while((t[i++]=s[j++])!='\0'); 
}
//���ַ���s���뵽t��ǰn���ַ��� 
void strnins(char t[],char s[],int n)
{
	char mid[100];
	codel(t,mid,n);
	strcate(t,s);
	strcate(t,mid);
}
int strlen(char s[]) 
{
	int i=0;
	while(s[i++]!='\0');
	return i;
}
//����ĳ�ַ������Ƿ��������ַ��������س��ִ��� 
int strfound(char s[],char c)
{
	int count=0;
	for(int i=0;i<strlen(s);i++)
	{
		if(c==s[i])
			count++;
	}
	if(count==0)
	printf("���ַ������޸��ַ���"); 
	else
	return count; 
} 
