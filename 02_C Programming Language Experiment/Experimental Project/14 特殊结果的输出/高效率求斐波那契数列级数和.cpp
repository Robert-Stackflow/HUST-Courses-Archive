#include<stdio.h>
long long fabonacci(int n)
{
	long long sum;
		if(n == 1) sum = 1;
		else if(n == 2) sum =2;
		else {
			long long a[]= {1,1}; 
			sum = 2;  //��һ��a1�͵ڶ���a2�ȼ�
			for(int i=2;i<n;i++){
				a[i%2]=a[0]+a[1];
				sum += a[i%2];
			}
		}
		return sum;
}
int main (void)
{
	int k;
	scanf("%d",&k);
	printf("%lld\n",fabonacci(k));
	return 0;
}

