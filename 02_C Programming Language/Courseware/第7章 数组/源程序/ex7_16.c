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
		j++;            /* 计算首部空白字符的个数 */
	i=l-1;   /* i为字符串最后一个字符的下标，即′\0′前面一个字符的下标 */
	while(s[i-k]== ' '||s[i-k]== '\t'||s[i-k]== '\n'||s[i-k]== '\r')
		k++;        /* 计算尾部空白字符的个数 */
	num=l-j-k;/*计算非空白字符的个数 */
	for(i=0;i<num;i++)
		s[i]=s[i+j];/*将第1个非空白字符s[0+j]复制到s[0],...*/
	s[num]='\0';/*赋'\0',形成字符串*/
	return strlen(s);/*返回去掉空白字符后的串长度*/
}
int strlen(char s[])
{	int j=0;
	while(s[j]!= '\0') j++;  /* 可以用while(s[j++])，这样更简洁 */
	return j;
}