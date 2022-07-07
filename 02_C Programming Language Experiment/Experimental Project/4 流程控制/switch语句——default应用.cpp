#include<stdio.h>
int main(void)
{
	int c;
	scanf("%d",&c);
	switch(c)
	{
		case 1:printf("1\n");break;
		case 2:printf("2\n");break;
		case 3:printf("3\n");break;
		default:printf("oh!%d\n",c);
		case 5:printf("5\n");
		case 6:printf("6\n");
	}
	printf("!!!%d",c);
	return 0;
} 
