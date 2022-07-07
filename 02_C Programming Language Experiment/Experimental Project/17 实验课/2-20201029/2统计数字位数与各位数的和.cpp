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
int SumofFigure(int y)
{
	int sum=0;
 	while(y!=0)       
 	{
  	sum+=y%10;
  	y=y/10;
 	}
 	return sum;
}
int main(void)
{
	long long unsigned s;
	int length,sum;
	scanf("%llu",&s);
	length=len(s);
	sum=SumofFigure(s);
	printf("%llu是%d位数,各位数字的和是%d",s,length,sum);
	return 0;
}
