#include<stdio.h>
int main(void)
{
	char c1,c2,c3;
	//空格和换行符也作为一个字符可以被读取 
	//空格的值是32，换行符是10
	//在连续出现gets函数时可以通过getchar()语句吸收换行符或空格 
	c1=getchar();
	c2=getchar();
	c3=getchar();
	printf("\n%c%c%c",c1,c2,c3);
	printf("\n%d %d %d",c1,c2,c3);
	return 0;
 } 
