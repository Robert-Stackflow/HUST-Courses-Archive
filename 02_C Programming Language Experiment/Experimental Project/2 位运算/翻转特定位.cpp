#include<stdio.h> 
int main(void)
{
	int x,p,n,result;
	scanf("%d%d%d",&x,&p,&n); 
	result=x ^(p != 31?(((((-1)>>(p+1-n)<<(p+1-n)<<(31-p))>>1)&2147483647)>>(30-p)):((-1)>>(32-n)<<(32-n)));
	printf("%d",result);
	return 0; 
}
