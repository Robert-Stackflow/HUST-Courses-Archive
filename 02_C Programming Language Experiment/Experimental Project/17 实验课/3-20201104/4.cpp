#include<stdio.h> 
int main(void) 
{
	char a,b;
	printf("请输入一段正文，并以Ctrl+Z结束:\n") ;
	while((b=getchar())!=EOF)
	{
		if(!(a==32&&b==32))//如果前后两个字符均为空格，则只输出一个 
		putchar(b);
		a=b;//将后一个字符赋给前一个字符 
	}
	return 0;
}
