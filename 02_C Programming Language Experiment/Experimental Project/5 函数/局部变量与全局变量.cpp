#include<stdio.h>
int num;
void test();//若该函数有形参呢？ 
int main(void)
{
	num=10;//删去这一行呢？删去int呢？ 
	{
		int num=20;//删去int呢？ 
		printf("%d\n",num);
	}
	test();
	printf("%d\n",num);	
	return 0;
}

void test()
{
	printf("%d\n",num);
	num=30;//加上int呢? 
	printf("%d\n",num);
}

/*int main (void)
{
	int a=2,b=4;
	printf("a=%d,b=%d\n",a,b);
	{
		int a;
		a=3,b=5;
		printf("a=%d,b=%d\n",a,b);
	}
	printf("a=%d,b=%d\n",a,b);
 } */
