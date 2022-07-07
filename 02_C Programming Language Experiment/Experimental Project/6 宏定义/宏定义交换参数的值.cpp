#include<stdio.h>
#define  swap(x,y)  {x=x^y;y=x^y;x=x^y;} 
int main(void)
{
	int x,y;
	scanf("%d%d",&x,&y);
	swap(x,y);
	printf("x=%d,y=%d",x,y);
	return 0;
}		 
