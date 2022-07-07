#include<stdio.h>
int main(void)
{
	char c;
	//将输入的字符转换为大写字母 
	putchar(((c=getchar())>='a'&&c<='z')?c-'a'+'A':c);
	return 0;
 } 
