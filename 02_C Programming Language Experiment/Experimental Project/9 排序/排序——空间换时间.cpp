#include<stdio.h>
#define NUM 3
#define RAGE 1000 
int main(void)
{
	int num[RAGE]={0};
	int value=1;
	printf("���������֣�\n");
	for(int i=0;i<NUM;i++)
	{
		scanf("%d",&value);
		num[value]=1;
	}
	printf("����õ��Ľ���ǣ�"); 
	for(int i=0;i<=RAGE;i++)
	{	
		if(num[i]==1)
			printf("%i\t",i);
	}
	return 0;
}
