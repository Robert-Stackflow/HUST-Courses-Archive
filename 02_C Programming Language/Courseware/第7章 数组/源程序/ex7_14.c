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
	while(t[j++]!='\0') ; /*将下标j移至t串的′\0′后面*/
			j--;	/*调整，将下标j移至t串的′\0′位置*/
	while((t[j++]=s[k++])) ;/* s串连接到t串的尾部*/
	return t;
}
