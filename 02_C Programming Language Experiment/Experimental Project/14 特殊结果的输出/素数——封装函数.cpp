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
		printf("����һ��������\n");
	else
		printf("�ⲻ��һ��������\n");
	return 0;
}

