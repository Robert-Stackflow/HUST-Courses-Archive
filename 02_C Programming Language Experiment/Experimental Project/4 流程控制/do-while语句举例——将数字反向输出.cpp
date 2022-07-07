#include<stdio.h> 
int main(void)
{
	int data=0,a,b;
	scanf("%d",&data);
	do
	{
		putchar(data%10+'0');
	}while((data/=110)!=0);
	return 0;
}
