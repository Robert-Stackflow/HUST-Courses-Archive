#include<stdio.h> 
//注意有无break的区别 
int main(void)
{
	int i=1;
	switch (i)
	{
	case 0:printf("%d\t",i);break; 
	case 1:printf("%d\t",i++);break;
	case 2:printf("%d\t",i++);break;
	case 3:printf("%d\t",i++);break;
	default:printf("\n");break;
	}
//	printf("%d\n",i); 
	return 0;
}
