#include<stdio.h>
#define scale 100000//�ɸı������������Χ 
int main()
{
	printf("������һ����Χ��[4,1000000]֮���ֵ��"); 
	long long i, j, a[scale],prime[scale];
	for (a[0]=a[1]=0,i=2;i<scale;i++)
		a[i]=1;
	for (i=2;i<scale;i++)
	{
		if(a[i]){
			for (j=i*2;j<scale;j+=i)
				a[j]=0;//ɸ�������ı��� 
		}
	}
	long long n=0;
	for(i=2;i<scale;++i)
	{
		if(a[i])
		{
			prime[n]=i;
			++n;//�����е��±꣨������������������ 
		}
	}
	long long m;
	scanf("%lld",&m);
	long long q=0;
	for (;prime[q+1]<m;q++)//��������������������� 
	{
		if(prime[q+1]-prime[q]==2)
		printf("(%lld,%lld)\n",prime[q],prime[q+1]);
	}
	return 0;
}
