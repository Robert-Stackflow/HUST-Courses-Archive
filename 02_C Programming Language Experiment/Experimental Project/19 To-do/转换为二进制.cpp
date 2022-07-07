#include<stdio.h> 
//转换为二进制数 
int main(void)
{
	int x,n,s[1000],i=0;
	n=x%2;
	for (;;++i)
	if (n)
		s[i]=0;
		n=x%2;
	else
		s[i]=1;
		n=x;
	 
}
