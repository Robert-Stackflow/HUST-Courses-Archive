#include<stdio.h>
int num;
void test();//���ú������β��أ� 
int main(void)
{
	num=10;//ɾȥ��һ���أ�ɾȥint�أ� 
	{
		int num=20;//ɾȥint�أ� 
		printf("%d\n",num);
	}
	test();
	printf("%d\n",num);	
	return 0;
}

void test()
{
	printf("%d\n",num);
	num=30;//����int��? 
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
