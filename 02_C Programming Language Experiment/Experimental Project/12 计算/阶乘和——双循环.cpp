#include<stdio.h>
int main(void)
{
	long long factorial=1,sum=0; 
	for(int x=1;x<=20;x++)
	{
		factorial*=x;
		sum+=factorial;
	} 
	printf("�����������ǰ��ʮ�����Ľ׳˵ĺ���%lld",sum);
	return 0;
 } 
