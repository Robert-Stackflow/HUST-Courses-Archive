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


//ȡ�ɵķ���������ȫ�ֱ���
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
