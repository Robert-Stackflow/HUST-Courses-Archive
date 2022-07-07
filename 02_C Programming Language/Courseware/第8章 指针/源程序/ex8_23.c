#include "stdio.h"
#include "ctype.h"
#include "string.h"
#define  MAXLEN    63   /* �ַ�������󳤶� */
void getid(char *,int);
int isid(char *);
int iskey(char *);
int main(void)
{	char id[MAXLEN+1];
 	printf("Input an identifier\n");
 	getid(id,MAXLEN);/*�����Ȳ�����MAXLEN���ַ���������s*/
 	if(isid(id))  printf("%s is an identifier.\n",id);
 	else  printf("%s is not an identifier.\n",id);
	return 0;
}
void getid(char *s,int lim)/*����һ�����Ȳ�����lim���ַ���������s*/
{	char c;
 	while(lim-->0&&(c=getchar())!='\n')
    	*s++ = c;
 	*s='\0';
}
int isid(char * t)/*t�Ǳ�ʶ������������1�����򣬷���0*/
{	char *s=t;
  	if( !isalpha(*t) && *t!= '_')  return 0;/*������ĸ���»��ߣ�����0*/
  	for(t++;*t!='\0';t++)/*�������ַ�������ĸ�����֡����»��ߣ�����0*/
     	if(!(isdigit(*t)||isalpha(*t)||*t=='_'))  return 0;
  	if(iskey(s)) return 0;/*�Ա�ʶ��s����һ���ж��Ƿ��ǹؼ���*/
 	return 1;
}
int iskey(char *s)/*��s�ǹؼ��֣���������1������,����0*/
{	char *keyword[]={/*keyword�е�ÿ��Ԫ�ض�ָ���ض��Ĺؼ����ַ���*/
	"auto", "_Bool",   "break",  "case",   "char", "_Complex",
	"const","continue","default","restrict","do",  "double",
	"else", "enum",    "extern", "float",  "for",   "goto",
	"if", "_Imaginary","inline", "int",    "long", "register",
	"return", "short", "signed", "sizeof", "static","struct",
	"switch","typedef","union", "unsigned","void", "volatile",
	"while","" };
 	int i;
  	for(i=0;*keyword[i]!='\0';i++)/*����ʶ��s��ÿ����*/
     	if(!strcmp(s,keyword[i])) return 1;/*���ֱȽϣ��Ƿ���1*/
  	return 0;/*�񷵻�0*/
}
