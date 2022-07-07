#include<stdio.h>
int change(int *p) 
{
	*p=30;
}
int main(void)
{
	int x=10;
	change(&x);
	printf("%d",x);
	return 0;
}


//取巧的方法：定义全局变量
/*
int x;
int change() 
{
	x=30;
}
int main(void)
{
	x=10;
	change();
	printf("%d",x);
	return 0;
}*/
