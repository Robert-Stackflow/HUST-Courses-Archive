#include<stdio.h> 
int main(void)
{
	int x=-1,max;
	printf("请输入一批以零结尾的整数：\n");
	scanf("%d",&x);
	max=x;
	for(;x!=0;)
	{
		scanf("%d",&x);
		if(max<x)
			max=x;
	}
	printf("最大值是%d",max);
	return 0;
}
