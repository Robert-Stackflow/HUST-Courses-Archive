#include "stdio.h"
int trim(char s[]);
int strlen(char s[]);
int main(void)
{
	char s[]="    they are workers.you are students.    ";
	printf("length=%d\n",trim(s));
	return 0;
}
int trim(char s[])
{	int i,num,j=0,k=0,l=strlen(s);
	while(s[j]== ' '||s[j]== '\t'||s[j]== '\n'||s[j]== '\r') 
		j++;            /* �����ײ��հ��ַ��ĸ��� */
	i=l-1;   /* iΪ�ַ������һ���ַ����±꣬����\0��ǰ��һ���ַ����±� */
	while(s[i-k]== ' '||s[i-k]== '\t'||s[i-k]== '\n'||s[i-k]== '\r')
		k++;        /* ����β���հ��ַ��ĸ��� */
	num=l-j-k;/*����ǿհ��ַ��ĸ��� */
	for(i=0;i<num;i++)
		s[i]=s[i+j];/*����1���ǿհ��ַ�s[0+j]���Ƶ�s[0],...*/
	s[num]='\0';/*��'\0',�γ��ַ���*/
	return strlen(s);/*����ȥ���հ��ַ���Ĵ�����*/
}
int strlen(char s[])
{	int j=0;
	while(s[j]!= '\0') j++;  /* ������while(s[j++])����������� */
	return j;
}