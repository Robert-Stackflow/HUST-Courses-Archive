#include<stdio.h> 
int main(void)
{
	unsigned long int x;
	int a,b,c,d;
	char e;
	printf("������IP��ַ��\n");
	while(scanf("%lu",&x)!=EOF)
	{
	a=x>>24;
	b=x>>16&0x000000ff;
	c=x>>8& 0x000000ff;
	d=x&0x000000ff;
	printf("%d.%d.%d.%d\n",a,b,c,d);
	printf("\n������IP��ַ��\n");
	} 
	return 0;	
}
