#include<stdio.h> 
#include<math.h>
long isprime(long n)//����һ�������ж������� 
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
long isMasonNumber(long num)//����һ�������ж���÷ɭ�� 
{
        int flag=0;
		if (((num+1)& (num))==0)
        	flag=1;    
    	return flag;
}
int count(long x)//����һ����ĳ����2�ļ��η��ĺ��� 
	{
	int count=0;
	int total=1;
	while(total<x)
	{
    	total = total * 2;
    	++count;
	}
	if (total == x)
    	return count;
}

int main(void)
{
	long i=2,m;
	printf("������һ�����ȴ������ĳ�������\n");
	scanf("%d",&m);
	for(;i<=m;++i)
	{
		if(isMasonNumber(i))//ifѭ����Ƕ�ף����ж������������ж��Ƿ�Ϊ÷ɭ���� 
		{
			if(isprime(i))

				printf("M(%d)=%ld\n",count(i+1),i);//��ʾ����� 	
		}
	}
	return 0; 
}
