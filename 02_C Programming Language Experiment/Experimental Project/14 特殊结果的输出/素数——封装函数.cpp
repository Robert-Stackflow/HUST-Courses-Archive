#include<stdio.h>
#include<math.h>
int isprime(int n)
{
	int flag=1;
	for(int i=2;i<=sqrt(n);i++)
	{
			if(n%i==0)
			{
				flag=0;
				break;
			}
	}
	return flag;			
} 
int main()
{
	int x;
	scanf("%d",&x);
	if (isprime(x))
		printf("这是一个素数！\n");
	else
		printf("这不是一个素数！\n");
	return 0;
}

