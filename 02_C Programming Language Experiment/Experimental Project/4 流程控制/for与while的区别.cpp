#include<stdio.h> 
int main(void)
{
	for(int i=0;i<10;++i)
		printf("%d ",i);
//	printf("%d",i);//for������i���ͷ��� 
	int i=0;
	while(i<10)
	{ 
		printf("%d\n",i);
		++i;
	} 
	printf("i:%d",i);
	return 0;
}
