#include<stdio.h> 
int main(void)
{
	int number,x,y,z;
	printf("请输入一个三位数："); 
	scanf("%d",&number);
	z=number/100;
	y=number/10%10;
	x=number%10;
	if(y>x&&y>z)
		printf("这是一个伞数\n") ;
	else
		printf("这不是一个伞数\n") ;
	return 0;
}
