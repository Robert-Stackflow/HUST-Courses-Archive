#include "stdio.h"
char * strcat(char t[],char s[]);
int main(void)
{
	char t[80]="there is a boat ",s[]="on the lake.";
	strcat(t,s);
	printf("%s\n",t);
	return 0;
}
char * strcat(char t[],char s[])
{	int j=0,k=0;
	while(t[j++]!='\0') ; /*���±�j����t���ġ�\0�����*/
			j--;	/*���������±�j����t���ġ�\0��λ��*/
	while((t[j++]=s[k++])) ;/* s�����ӵ�t����β��*/
	return t;
}
