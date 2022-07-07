#include<stdio.h>
int len(int x)
{
	int i=0;
	do
		{
		x/=10;	
		++i;
		}
	while(x!=0);
	return i; 
}
void reverse(int x)
{
    do
    	putchar(x%10+'0');
    while((x/=10)!=0);
}
int main(void)
{
	int s,length;
	scanf("%d",&s);
	length=len(s);
	printf("%d\n",length);
	reverse(s);
	return 0;
}
