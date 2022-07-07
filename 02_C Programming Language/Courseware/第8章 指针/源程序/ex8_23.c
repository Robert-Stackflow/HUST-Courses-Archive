#include "stdio.h"
#include "ctype.h"
#include "string.h"
#define  MAXLEN    63   /* 字符串的最大长度 */
void getid(char *,int);
int isid(char *);
int iskey(char *);
int main(void)
{	char id[MAXLEN+1];
 	printf("Input an identifier\n");
 	getid(id,MAXLEN);/*读长度不超过MAXLEN的字符串到数组s*/
 	if(isid(id))  printf("%s is an identifier.\n",id);
 	else  printf("%s is not an identifier.\n",id);
	return 0;
}
void getid(char *s,int lim)/*读入一个长度不超过lim的字符串到数组s*/
{	char c;
 	while(lim-->0&&(c=getchar())!='\n')
    	*s++ = c;
 	*s='\0';
}
int isid(char * t)/*t是标识符，函数返回1；否则，返回0*/
{	char *s=t;
  	if( !isalpha(*t) && *t!= '_')  return 0;/*不是字母或下划线，返回0*/
  	for(t++;*t!='\0';t++)/*若后续字符不是字母、数字、或下划线，返回0*/
     	if(!(isdigit(*t)||isalpha(*t)||*t=='_'))  return 0;
  	if(iskey(s)) return 0;/*对标识符s，进一步判断是否是关键字*/
 	return 1;
}
int iskey(char *s)/*若s是关键字，函数返回1；否则,返回0*/
{	char *keyword[]={/*keyword中的每个元素都指向特定的关键字字符串*/
	"auto", "_Bool",   "break",  "case",   "char", "_Complex",
	"const","continue","default","restrict","do",  "double",
	"else", "enum",    "extern", "float",  "for",   "goto",
	"if", "_Imaginary","inline", "int",    "long", "register",
	"return", "short", "signed", "sizeof", "static","struct",
	"switch","typedef","union", "unsigned","void", "volatile",
	"while","" };
 	int i;
  	for(i=0;*keyword[i]!='\0';i++)/*将标识符s与每个关*/
     	if(!strcmp(s,keyword[i])) return 1;/*键字比较，是返回1*/
  	return 0;/*否返回0*/
}
