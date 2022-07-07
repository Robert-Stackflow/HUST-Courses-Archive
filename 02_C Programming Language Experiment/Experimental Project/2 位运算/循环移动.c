#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x,n,result; 
	scanf("%d%d",&x,&n);
	result=x<<(32-(n%32))|x>>(n%32);
	printf("%d",result);
	return 0;
}
