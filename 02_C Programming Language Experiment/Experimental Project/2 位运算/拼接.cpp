//将整数p的高字节作为结果的低字节，将q的低字节作为结果的高字节 
#include<stdio.h> 
int main(void)
{
	int p,q,s;
	scanf("%d%d",&p,&q);
	s=((p>>8)&255)|(q<<8);
	printf("%d",s);
	return 0;
}
