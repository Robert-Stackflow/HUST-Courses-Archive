#include<stdio.h>
//�ж��Ǻ��� 
int NotPrime(int x)
{
	int i,k,flag=0;
	for(i=2,k=x>>1;i<=k;i++)
	{
		if(x%i==0)
			{
				flag=1;
				break;
			}
	}	
	return flag;
}
//�ж��Ǵ������ 
int pure(int x)
{
	int flag=0,count=0;
	for(int j=0;j<3;++j) 
	{
		if(NotPrime(x))
			count++; 
		x/=10;
	}
	if(count==3)
		flag=1;
	return flag;
} 
int main(void)
{
	int num=0;
	printf("���������\n");
	for(int x=100;x<=999;++x)
		{
			if(pure(x))
			{
				printf("%d\t",x);
				num++;
				if(num%10==0)
					printf("\n");
			} 
		}
	return 0;
 } 
