#include<stdio.h>
#define NUM 3
#define RAGE 1000 
int main(void)
{
	int num[RAGE]={0};
	int value=1;
	printf("请输入数字：\n");
	for(int i=0;i<NUM;i++)
	{
		scanf("%d",&value);
		num[value]=1;
	}
	printf("排序得到的结果是："); 
	for(int i=0;i<=RAGE;i++)
	{	
		if(num[i]==1)
			printf("%i\t",i);
	}
	return 0;
}
