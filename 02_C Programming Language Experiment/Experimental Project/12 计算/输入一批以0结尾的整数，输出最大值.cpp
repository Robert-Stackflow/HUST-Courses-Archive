#include<stdio.h> 
int main(void)
{
	int x=-1,max;
	printf("������һ�������β��������\n");
	scanf("%d",&x);
	max=x;
	for(;x!=0;)
	{
		scanf("%d",&x);
		if(max<x)
			max=x;
	}
	printf("���ֵ��%d",max);
	return 0;
}
